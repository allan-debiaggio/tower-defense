#include "WaveManager.h"
#include <random>

WaveManager::WaveManager(int numWaves, int enemiesPerWave, const std::vector<Path> &paths)
    : numWaves_(numWaves), enemiesPerWave_(enemiesPerWave), currentWave_(0), waveActive_(false), paths_(paths), rng_(std::random_device{}()), pathDist_(0, paths.size() - 1) {}

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
    size_t pathIndex = pathDist_(rng_);
    activeEnemies_.push_back(std::make_unique<GoombaEnemy>(paths_[pathIndex]));
    ++spawnedThisWave_;
    spawnTimer_ -= spawnInterval_;
  }
}

size_t WaveManager::getNumPaths() const
{
  return paths_.size();
}