#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Path.h"
#include <random>
#include <functional>

class WaveManager
{
public:
  using EnemyFactory = std::function<std::unique_ptr<Enemy>(const Path &)>;
  WaveManager(int numWaves, int baseEnemiesPerWave, const std::vector<Path> &paths, const std::vector<EnemyFactory> &enemyFactories = {});
  bool hasNextWave() const;
  void startNextWave();
  bool isWaveActive() const;
  std::vector<std::unique_ptr<Enemy>> &getActiveEnemies();
  const std::vector<std::unique_ptr<Enemy>> &getActiveEnemies() const;
  int getCurrentWave() const;
  void update(float dt); // Call this every tick to spawn enemies over time
  size_t getNumPaths() const;
  void setEnemyFactories(const std::vector<EnemyFactory> &enemyFactories);
  int getBaseEnemiesPerWave() const { return baseEnemiesPerWave_; }
  void reset();
  int getNumWaves() const { return numWaves_; }

private:
  int numWaves_;
  int baseEnemiesPerWave_;
  int currentWave_; // 1-based, incremented before each wave starts
  bool waveActive_;
  std::vector<std::unique_ptr<Enemy>> activeEnemies_;
  const std::vector<Path> &paths_;
  float spawnInterval_ = 1.0f; // seconds between spawns
  float spawnTimer_ = 0.0f;    // time since last spawn
  int spawnedThisWave_ = 0;    // how many enemies spawned in current wave
  std::mt19937 rng_;
  std::uniform_int_distribution<size_t> pathDist_;
  std::vector<EnemyFactory> enemyFactories_;
  std::uniform_int_distribution<size_t> enemyTypeDist_;
  void spawnWave();
};