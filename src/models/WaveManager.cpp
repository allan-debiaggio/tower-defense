#include "WaveManager.h"
#include <random>

WaveManager::WaveManager(int numWaves, int enemiesPerWave, const Path &path)
    : numWaves_(numWaves), enemiesPerWave_(enemiesPerWave), currentWave_(0), waveActive_(false), path_(path) {}

bool WaveManager::hasNextWave() const
{
  return currentWave_ < numWaves_;
}

void WaveManager::startNextWave()
{
  if (!hasNextWave())
    return;
  spawnWave();
  waveActive_ = true;
  ++currentWave_;
}

bool WaveManager::isWaveActive() const
{
  return waveActive_;
}

std::vector<std::unique_ptr<Enemy>> &WaveManager::getActiveEnemies()
{
  return activeEnemies_;
}

int WaveManager::getCurrentWave() const
{
  return currentWave_;
}

void WaveManager::spawnWave()
{
  activeEnemies_.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  // For now, only GoombaEnemy; extend here for more types
  for (int i = 0; i < enemiesPerWave_; ++i)
  {
    // Placeholder for random enemy type selection
    // int type = std::uniform_int_distribution<>(0, 0)(gen); // Only one type for now
    activeEnemies_.push_back(std::make_unique<GoombaEnemy>(path_));
  }
}