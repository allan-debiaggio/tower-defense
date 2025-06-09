#include "WaveManager.h"
#include <random>
#include <iostream>

WaveManager::WaveManager(int numWaves, int baseEnemiesPerWave, const std::vector<Path> &paths, const std::vector<EnemyFactory> &enemyFactories)
    : numWaves_(numWaves), baseEnemiesPerWave_(baseEnemiesPerWave), currentWave_(0), waveActive_(false), paths_(paths), rng_(std::random_device{}()), pathDist_(0, paths.size() - 1), enemyFactories_(enemyFactories), enemyTypeDist_(0, enemyFactories.empty() ? 0 : enemyFactories.size() - 1) {}

void WaveManager::setEnemyFactories(const std::vector<EnemyFactory> &enemyFactories)
{
  enemyFactories_ = enemyFactories;
  enemyTypeDist_ = std::uniform_int_distribution<size_t>(0, enemyFactories_.empty() ? 0 : enemyFactories_.size() - 1);
}

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
  std::cout << "[DEBUG] startNextWave: currentWave_=" << currentWave_ << " numWaves_=" << numWaves_ << std::endl;
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
  int enemiesPerWave = baseEnemiesPerWave_ + currentWave_; // Increase with level
  while (spawnedThisWave_ < enemiesPerWave && spawnTimer_ >= spawnInterval_)
  {
    size_t pathIndex = pathDist_(rng_);
    size_t enemyType = enemyFactories_.empty() ? 0 : enemyTypeDist_(rng_);
    if (!enemyFactories_.empty())
      activeEnemies_.push_back(enemyFactories_[enemyType](paths_[pathIndex]));
    else
      activeEnemies_.push_back(std::make_unique<GoombaEnemy>(paths_[pathIndex]));
    ++spawnedThisWave_;
    spawnTimer_ -= spawnInterval_;
  }
  // End wave if all enemies spawned and all are gone
  if (spawnedThisWave_ >= enemiesPerWave && activeEnemies_.empty())
  {
    waveActive_ = false;
  }
}

size_t WaveManager::getNumPaths() const
{
  return paths_.size();
}