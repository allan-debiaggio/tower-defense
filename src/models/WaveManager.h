#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Path.h"
#include <random>

class WaveManager
{
public:
  WaveManager(int numWaves, int enemiesPerWave, const std::vector<Path> &paths);
  bool hasNextWave() const;
  void startNextWave();
  bool isWaveActive() const;
  std::vector<std::unique_ptr<Enemy>> &getActiveEnemies();
  int getCurrentWave() const;
  void update(float dt); // Call this every tick to spawn enemies over time
  size_t getNumPaths() const;

private:
  int numWaves_;
  int enemiesPerWave_;
  int currentWave_;
  bool waveActive_;
  std::vector<std::unique_ptr<Enemy>> activeEnemies_;
  const std::vector<Path> &paths_;
  float spawnInterval_ = 1.0f; // seconds between spawns
  float spawnTimer_ = 0.0f;    // time since last spawn
  int spawnedThisWave_ = 0;    // how many enemies spawned in current wave
  std::mt19937 rng_;
  std::uniform_int_distribution<size_t> pathDist_;
  void spawnWave();
};