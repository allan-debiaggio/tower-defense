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

void PlayingState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PlayingState\n";
  auto &level = *manager.getCurrentLevel();
  auto &waveManager = level.getWaveManager();
  if (!waveManager.isWaveActive() && waveManager.hasNextWave())
  {
    waveManager.startNextWave();
    int waveNum = waveManager.getCurrentWave();
    int enemiesThisWave = level.getWaveManager().getBaseEnemiesPerWave() + waveNum;
    std::cout << "\n--- Wave " << waveNum << " begins! Enemies this wave: " << enemiesThisWave << " ---\n";
  }
}

void PlayingState::update(GameManager &manager, float dt)
{
  auto &level = *manager.getCurrentLevel();
  auto &waveManager = level.getWaveManager();
  auto &player = manager.getPlayer();

  // Static list of projectiles for the session
  static std::list<std::unique_ptr<Projectile>> activeProjectiles;

  // Auto-tick: run several small updates per Enter
  const int numTicks = 5;
  const float tickDt = dt / numTicks;
  for (int tick = 0; tick < numTicks; ++tick)
  {
    waveManager.update(tickDt);
    auto &enemies = waveManager.getActiveEnemies();

    // 1. Update all enemies (move them)
    for (auto &enemy : enemies)
    {
      if (enemy && enemy->isAlive())
      {
        enemy->update(tickDt);
      }
    }

    // 2. Towers shoot, collect new projectiles
    for (int y = 0; y < level.getHeight(); ++y)
    {
      for (int x = 0; x < level.getWidth(); ++x)
      {
        Tower *tower = level.getTower(x, y);
        if (tower)
        {
          std::vector<Enemy *> enemyPtrs;
          for (auto &ep : enemies)
            if (ep && ep->isAlive())
              enemyPtrs.push_back(ep.get());
          auto projectiles = tower->update(tickDt, enemyPtrs);
          for (auto *proj : projectiles)
          {
            if (proj)
            {
              std::cout << "[DEBUG] Tower at (" << x << "," << y << ") shoots!\n";
              activeProjectiles.emplace_back(proj);
            }
          }
        }
      }
    }

    // 3. Update all projectiles, print hits, and remove hit projectiles
    for (auto it = activeProjectiles.begin(); it != activeProjectiles.end();)
    {
      auto &proj = *it;
      float beforeHP = proj->getTarget() ? proj->getTarget()->getHealth() : 0;
      proj->update(tickDt);
      float afterHP = proj->getTarget() ? proj->getTarget()->getHealth() : 0;
      if (proj->hasHit())
      {
        if (beforeHP != afterHP)
        {
          std::cout << "\033[32m[DEBUG] Projectile hit! Enemy HP: " << beforeHP << " -> " << afterHP << "\033[0m\n";
        }
        it = activeProjectiles.erase(it);
      }
      else
      {
        ++it;
      }
    }

    // 4. Remove dead enemies, print deaths, and handle enemies reaching the end
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      if (*it && !(*it)->isAlive())
      {
        auto pos = (*it)->getPosition();
        if (!(*it)->hasReachedEnd())
        {
          std::cout << "\033[33m[DEBUG] Enemy at (" << pos.first << ", " << pos.second << ") killed! +5 coins\033[0m\n";
          player.addCoins(5); // Reward for kill
        }
        it = enemies.erase(it);
      }
      else if (*it && (*it)->isAlive() && (*it)->hasReachedEnd())
      {
        auto pos = (*it)->getPosition();
        std::cout << "\033[31m[DEBUG] Enemy at (" << pos.first << ", " << pos.second << ") reached the castle! You lose a life.\033[0m\n";
        player.loseLife();
        it = enemies.erase(it);
      }
      else
      {
        ++it;
      }
    }

    // Debug: print active enemies
    std::cout << "[DEBUG] Enemies: ";
    if (enemies.empty())
    {
      std::cout << "None";
    }
    else
    {
      for (const auto &enemyPtr : enemies)
      {
        if (enemyPtr)
        {
          auto pos = enemyPtr->getPosition();
          std::cout << "(x=" << pos.first << ", y=" << pos.second << ", hp=" << enemyPtr->getHealth() << ") ";
        }
      }
    }
    std::cout << "\n";
  }

  std::cout << "Player: " << manager.getPlayerName() << " | Coins: " << player.getCoins() << " | Lives: " << player.getLives() << "\n";
  std::cout << "Current Wave: " << waveManager.getCurrentWave() << "\n";

  // Check for defeat
  if (player.getLives() <= 0)
  {
    std::cout << "You lost all your lives!\n";
    manager.setState(std::make_unique<GameOverState>());
    return;
  }
  // Check for victory
  if (!waveManager.hasNextWave() && !waveManager.isWaveActive() && waveManager.getActiveEnemies().empty())
  {
    std::cout << "All waves cleared!\n";
    manager.setState(std::make_unique<VictoryState>());
    return;
  }

  // If a wave just finished, offer upgrade/sell menu
  if (!waveManager.isWaveActive() && waveManager.hasNextWave())
  {
    std::cout << "\n--- Wave Complete! ---\n";
    handleUpgradeOrSell(manager, true);
    // Start the next wave after upgrade/sell
    waveManager.startNextWave();
    // Print wave info
    int waveNum = waveManager.getCurrentWave();
    int enemiesThisWave = level.getWaveManager().getBaseEnemiesPerWave() + waveNum;
    std::cout << "\n--- Wave " << waveNum << " begins! Enemies this wave: " << enemiesThisWave << " ---\n";
  }
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
    manager.setState(std::make_unique<GameOverState>());
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