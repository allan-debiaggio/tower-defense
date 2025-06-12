#include <SFML/Graphics.hpp>
#include "src/models/LevelManager.h"
#include <memory>
#include "src/views/GameView.h"
#include "src/models/Tower.h"
#include <iostream>
#include "src/views/HUDView.h"
#include "src/controllers/TowerPlacementController.h"
#include <list>

int main()
{
  // Example level setup (10x5 grid, as in main.cpp)
  std::vector<std::pair<float, float>> waypoints = {{0, 2}, {5, 2}, {9, 2}};
  Path path(waypoints);
  std::vector<Path> paths = {path};
  int numWaves = 1;
  int enemiesPerWave = 2;
  std::unique_ptr<LevelManager> level = std::make_unique<LevelManager>(10, 5, paths, numWaves, enemiesPerWave);

  // Place a tower at (2,1) (buildable tile)
  if (!level->placeTower(2, 1, std::make_unique<FireFlowerTower>(std::make_pair(2.0f, 1.0f))))
  {
    std::cout << "Failed to place tower at (2,1): not buildable.\n";
  }

  // Start a wave
  level->getWaveManager().startNextWave();

  // Print all path waypoints at start
  if (!paths.empty())
  {
    std::cout << "[DEBUG] Path waypoints:";
    for (size_t i = 0; i < paths[0].getNumWaypoints(); ++i)
    {
      auto [wx, wy] = paths[0].getWaypoint(i);
      std::cout << " (" << wx << ", " << wy << ")";
    }
    std::cout << std::endl;
  }

  const unsigned int tileSize = 64;
  unsigned int width = level->getWidth();
  unsigned int height = level->getHeight();
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width * tileSize, height * tileSize)), "Tower Defense - SFML");

  GameView gameView(tileSize);
  HUDView hudView(width * tileSize, tileSize);

  Player player(30, 3);
  TowerPlacementController placementController(level.get(), &player, tileSize);
  std::list<std::unique_ptr<Projectile>> activeProjectiles;

  sf::Clock clock;
  while (window.isOpen())
  {
    while (auto eventOpt = window.pollEvent())
    {
      const sf::Event &event = *eventOpt;
      if (event.is<sf::Event::Closed>())
        window.close();
      // Handle tower placement events
      placementController.handleEvent(event, window);
    }
    // Update enemies (simulate time)
    float dt = clock.restart().asSeconds();
    dt = std::min(dt, 0.05f); // Cap dt to 0.05 seconds (20 FPS max step)
    level->getWaveManager().update(dt);
    // Update all enemies (move them)
    for (const auto &enemyPtr : level->getWaveManager().getActiveEnemies())
    {
      if (enemyPtr)
      {
        enemyPtr->update(dt);
      }
    }
    // Towers shoot, collect new projectiles
    for (int y = 0; y < level->getHeight(); ++y)
    {
      for (int x = 0; x < level->getWidth(); ++x)
      {
        Tower *tower = level->getTower(x, y);
        if (tower)
        {
          std::vector<Enemy *> enemyPtrs;
          for (const auto &ep : level->getWaveManager().getActiveEnemies())
            if (ep && ep->isAlive())
              enemyPtrs.push_back(ep.get());
          auto projectiles = tower->update(dt, enemyPtrs);
          for (auto *proj : projectiles)
          {
            if (proj)
              activeProjectiles.emplace_back(proj);
          }
        }
      }
    }
    // Update all projectiles, remove hit ones
    for (auto it = activeProjectiles.begin(); it != activeProjectiles.end();)
    {
      (*it)->update(dt);
      if ((*it)->hasHit() || (*it)->getTarget() == nullptr)
      {
        it = activeProjectiles.erase(it);
      }
      else
      {
        ++it;
      }
    }
    // Remove dead enemies, award coins, and handle enemies reaching the end
    auto &enemies = level->getWaveManager().getActiveEnemies();
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      if (*it && !(*it)->isAlive())
      {
        auto pos = (*it)->getPosition();
        if (!(*it)->hasReachedEnd())
        {
          player.addCoins(5); // Reward for kill
        }
        // Nullify projectiles targeting this soon-to-be-erased enemy
        for (auto &proj : activeProjectiles)
        {
          if (proj && proj->getTarget() == it->get())
          {
            // Access protected member: use a cast to Projectile* and set target_ directly
            struct ProjectileHack : Projectile
            {
              using Projectile::target_;
            };
            static_cast<ProjectileHack *>(proj.get())->target_ = nullptr;
          }
        }
        it = enemies.erase(it);
      }
      else if (*it && (*it)->isAlive() && (*it)->hasReachedEnd())
      {
        player.loseLife();
        it = enemies.erase(it);
      }
      else
      {
        ++it;
      }
    }

    window.clear(sf::Color::Black);
    gameView.render(window, *level);
    gameView.renderProjectiles(window, activeProjectiles);
    placementController.draw(window);
    hudView.render(window, player, *level);
    window.display();
  }
  return 0;
}