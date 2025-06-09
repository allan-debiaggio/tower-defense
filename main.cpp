#include "src/models/GameManager.h"
#include "src/models/LevelManager.h"
#include "src/models/Path.h"
#include "src/models/Enemy.h"
#include "src/models/Tower.h"
#include "src/models/MainMenuState.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
  GameManager manager;

  // --- Level 1: 1 path, 1 wave, 2 enemies per wave, 2 enemy types ---
  std::vector<std::pair<float, float>> waypoints1 = {{0, 2}, {5, 2}, {9, 2}};
  Path path1(waypoints1);
  std::vector<Path> paths1 = {path1};
  int numWaves1 = 1;
  int enemiesPerWave1 = 2;
  auto enemyFactories1 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<ParagoombaEnemy>(p); }};
  auto level1 = std::make_unique<LevelManager>(10, 5, paths1, numWaves1, enemiesPerWave1);
  level1->setEnemyFactories(enemyFactories1);
  manager.addLevel(std::move(level1));

  // --- Level 2: 2 paths, 2 waves, 3 enemies per wave, 3 enemy types ---
  std::vector<std::pair<float, float>> waypoints2a = {{0, 1}, {4, 1}, {9, 1}};
  std::vector<std::pair<float, float>> waypoints2b = {{0, 3}, {4, 3}, {9, 3}};
  Path path2a(waypoints2a);
  Path path2b(waypoints2b);
  std::vector<Path> paths2 = {path2a, path2b};
  int numWaves2 = 2;
  int enemiesPerWave2 = 3;
  auto enemyFactories2 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<KoopaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<ParagoombaEnemy>(p); }};
  auto level2 = std::make_unique<LevelManager>(10, 5, paths2, numWaves2, enemiesPerWave2);
  level2->setEnemyFactories(enemyFactories2);
  manager.addLevel(std::move(level2));

  // --- Level 3: 3 paths, 3 waves, 4 enemies per wave, 3 enemy types (Boss in last wave) ---
  std::vector<std::pair<float, float>> waypoints3a = {{0, 0}, {9, 0}};
  std::vector<std::pair<float, float>> waypoints3b = {{0, 2}, {9, 2}};
  std::vector<std::pair<float, float>> waypoints3c = {{0, 4}, {9, 4}};
  Path path3a(waypoints3a);
  Path path3b(waypoints3b);
  Path path3c(waypoints3c);
  std::vector<Path> paths3 = {path3a, path3b, path3c};
  int numWaves3 = 3;
  int enemiesPerWave3 = 4;
  auto enemyFactories3 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<KoopaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<BowserEnemy>(p); }};
  auto level3 = std::make_unique<LevelManager>(10, 5, paths3, numWaves3, enemiesPerWave3);
  level3->setEnemyFactories(enemyFactories3);
  manager.addLevel(std::move(level3));

  // Start the game
  manager.setState(std::make_unique<MainMenuState>());
  while (true)
  {
    manager.update(1.0f); // Simulate 1 second per loop
    manager.handleInput();
  }
  return 0;
}