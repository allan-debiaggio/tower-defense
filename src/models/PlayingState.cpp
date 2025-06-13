#include "PlayingState.h"
#include "GameManager.h"
#include "PausedState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include <iostream>
#include <memory>
#include <list>

namespace
{
  void handleUpgradeOrSell(GameManager &manager, bool allowSkip = true)
  {
    auto &level = *manager.getCurrentLevel();
    auto &player = manager.getPlayer();
    std::string menu = "You may upgrade (u) or sell (s) a tower";
    if (allowSkip)
      menu += ", or press Enter to continue.";
    std::cout << menu << "\nEnter your choice: ";
    std::string input;
    std::getline(std::cin, input);
    if (input == "u")
    {
      int x, y;
      std::cout << "Enter tower x y to upgrade: ";
      std::cin >> x >> y;
      std::cin.ignore();
      Tower *tower = level.getTower(x, y);
      if (!tower)
      {
        std::cout << "No tower at that position.\n";
      }
      else if (!tower->canUpgrade())
      {
        std::cout << "Tower cannot be upgraded further.\n";
      }
      else
      {
        std::cout << "Upgrade cost: " << tower->getUpgradeCost() << " coins. ";
        if (player.getCoins() < tower->getUpgradeCost())
        {
          std::cout << "Not enough coins!\n";
        }
        else
        {
          int coins = player.getCoins();
          if (tower->upgrade(coins))
          {
            player = Player(coins, player.getLives());
            std::cout << "Tower upgraded! Coins left: " << player.getCoins() << "\n";
          }
          else
          {
            std::cout << "Upgrade failed.\n";
          }
        }
      }
    }
    else if (input == "s")
    {
      int x, y;
      std::cout << "Enter tower x y to sell: ";
      std::cin >> x >> y;
      std::cin.ignore();
      Tower *tower = level.getTower(x, y);
      if (!tower)
      {
        std::cout << "No tower at that position.\n";
      }
      else
      {
        int value = tower->getSellValue();
        player.addCoins(value);
        level.removeTower(x, y);
        std::cout << "Tower sold for " << value << " coins. Coins now: " << player.getCoins() << "\n";
      }
    }
  }
} // end anonymous namespace

PlayingState::PlayingState() : m_windowWidth(800), m_windowHeight(600) {}

PlayingState::PlayingState(unsigned int windowWidth, unsigned int windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight) {}

void PlayingState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PlayingState (SFML)\n";
  m_level = manager.getCurrentLevel();
  m_player = &manager.getPlayer();
  const unsigned int tileSize = 64;
  m_gameView = std::make_unique<GameView>(tileSize);
  m_hudView = std::make_unique<HUDView>(m_level->getWidth() * tileSize, tileSize);
  m_placementController = std::make_unique<TowerPlacementController>(m_level, m_player, tileSize);
  m_activeProjectiles.clear();
  // Start the first wave if not already started
  auto &waveManager = m_level->getWaveManager();
  if (!waveManager.isWaveActive() && waveManager.hasNextWave())
    waveManager.startNextWave();
}

void PlayingState::update(GameManager &manager, float dt)
{
  auto &waveManager = m_level->getWaveManager();
  // Update enemies
  waveManager.update(dt);
  for (const auto &enemyPtr : waveManager.getActiveEnemies())
    if (enemyPtr)
      enemyPtr->update(dt);
  // Towers shoot, collect new projectiles
  for (int y = 0; y < m_level->getHeight(); ++y)
    for (int x = 0; x < m_level->getWidth(); ++x)
      if (Tower *tower = m_level->getTower(x, y))
      {
        std::vector<Enemy *> enemyPtrs;
        for (const auto &ep : waveManager.getActiveEnemies())
          if (ep && ep->isAlive())
            enemyPtrs.push_back(ep.get());
        auto projectiles = tower->update(dt, enemyPtrs);
        for (auto *proj : projectiles)
          if (proj)
            m_activeProjectiles.emplace_back(proj);
      }
  // Update projectiles, remove hit ones
  for (auto it = m_activeProjectiles.begin(); it != m_activeProjectiles.end();)
  {
    (*it)->update(dt);
    if ((*it)->hasHit() || (*it)->getTarget() == nullptr)
      it = m_activeProjectiles.erase(it);
    else
      ++it;
  }
  // Remove dead enemies, award coins, handle enemies reaching end
  auto &enemies = waveManager.getActiveEnemies();
  for (auto it = enemies.begin(); it != enemies.end();)
  {
    if (*it && !(*it)->isAlive())
    {
      if (!(*it)->hasReachedEnd())
        m_player->addCoins(5);
      // Nullify projectiles targeting this soon-to-be-erased enemy
      for (auto &proj : m_activeProjectiles)
        if (proj && proj->getTarget() == it->get())
        {
          struct ProjectileHack : Projectile
          {
            using Projectile::hit_;
            using Projectile::target_;
          };
          auto *hack = static_cast<ProjectileHack *>(proj.get());
          hack->target_ = nullptr;
          hack->hit_ = true; // Mark for removal
          std::cout << "[DEBUG] Nullified projectile target for erased enemy" << std::endl;
        }
      // Immediately remove all projectiles with null target
      for (auto pit = m_activeProjectiles.begin(); pit != m_activeProjectiles.end();)
      {
        if (!(*pit) || (*pit)->getTarget() == nullptr)
          pit = m_activeProjectiles.erase(pit);
        else
          ++pit;
      }
      it = enemies.erase(it);
    }
    else if (*it && (*it)->isAlive() && (*it)->hasReachedEnd())
    {
      m_player->loseLife();
      it = enemies.erase(it);
    }
    else
      ++it;
  }
  // Auto-start next wave if previous wave finished and more waves remain
  if (!waveManager.isWaveActive() && waveManager.hasNextWave() && waveManager.getActiveEnemies().empty())
  {
    std::cout << "[DEBUG] Starting next wave: " << (waveManager.getCurrentWave() + 1) << " of " << waveManager.getNumWaves() << std::endl;
    waveManager.startNextWave();
  }
  // Check for defeat
  if (m_player->getLives() <= 0)
  {
    manager.setState(std::make_unique<GameOverState>(m_windowWidth, m_windowHeight));
    return;
  }
  // Check for victory
  if (!waveManager.hasNextWave() && !waveManager.isWaveActive() && waveManager.getActiveEnemies().empty())
  {
    manager.setState(std::make_unique<VictoryState>(m_windowWidth, m_windowHeight, VictoryState::Mode::NextLevel));
    return;
  }
}

void PlayingState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager)
{
  m_placementController->handleEvent(event, window);
}

void PlayingState::draw(sf::RenderWindow &window)
{
  m_gameView->render(window, *m_level);
  m_gameView->renderProjectiles(window, m_activeProjectiles);
  m_placementController->draw(window);
  m_hudView->render(window, *m_player, *m_level);
}

void PlayingState::handleInput(GameManager &manager)
{
  std::cout << "Press p to pause, q to quit, u to upgrade, s to sell, or Enter to continue: ";
  std::string input;
  std::getline(std::cin, input);
  if (input == "p")
  {
    manager.setState(std::make_unique<PausedState>());
  }
  else if (input == "q")
  {
    manager.setState(std::make_unique<GameOverState>(m_windowWidth, m_windowHeight));
  }
  else if (input == "u" || input == "s")
  {
    handleUpgradeOrSell(manager, false);
  }
  // Otherwise, continue playing
}

void PlayingState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PlayingState\n";
}