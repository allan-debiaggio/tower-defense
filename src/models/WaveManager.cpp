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
  activeEnemies_.clear();
  spawnedThisWave_ = 0;
  spawnTimer_ = 0.0f;
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

void WaveManager::update(float dt)
{
  if (!waveActive_)
    return;
  spawnTimer_ += dt;
  while (spawnedThisWave_ < enemiesPerWave_ && spawnTimer_ >= spawnInterval_)
  {
    activeEnemies_.push_back(std::make_unique<GoombaEnemy>(path_));
    ++spawnedThisWave_;
    spawnTimer_ -= spawnInterval_;
  }
}