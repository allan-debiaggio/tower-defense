#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Path.h"

class WaveManager
{
public:
  WaveManager(int numWaves, int enemiesPerWave, const Path &path);
  bool hasNextWave() const;
  void startNextWave();
  bool isWaveActive() const;
  std::vector<std::unique_ptr<Enemy>> &getActiveEnemies();
  int getCurrentWave() const;

private:
  int numWaves_;
  int enemiesPerWave_;
  int currentWave_;
  bool waveActive_;
  std::vector<std::unique_ptr<Enemy>> activeEnemies_;
  const Path &path_;
  void spawnWave();
};