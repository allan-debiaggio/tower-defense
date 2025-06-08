#include "LevelManager.h"

LevelManager::LevelManager(int width, int height, const Path &path, int numWaves, int enemiesPerWave)
    : width_(width), height_(height), map_(height, std::vector<int>(width, 0)),
      path_(path), waveManager_(numWaves, enemiesPerWave, path_)
{
  towers_.resize(height_);
  for (int y = 0; y < height_; ++y)
    towers_[y].resize(width_);
  // Example: mark path tiles as 1, buildable as 2, rest as 0
  // (In a real game, this would be loaded from a file or generated)
  for (size_t i = 0; i < path_.getNumWaypoints(); ++i)
  {
    auto [x, y] = path_.getWaypoint(i);
    if (x >= 0 && y >= 0 && x < width_ && y < height_)
      map_[static_cast<int>(y)][static_cast<int>(x)] = 1;
  }
  // Mark all non-path tiles as buildable (2)
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      if (map_[y][x] == 0)
        map_[y][x] = 2;
    }
  }
}

int LevelManager::getWidth() const { return width_; }
int LevelManager::getHeight() const { return height_; }
bool LevelManager::isBuildable(int x, int y) const
{
  return x >= 0 && y >= 0 && x < width_ && y < height_ && map_[y][x] == 2 && !towers_[y][x];
}
bool LevelManager::placeTower(int x, int y, std::unique_ptr<Tower> tower)
{
  if (!isBuildable(x, y))
    return false;
  towers_[y][x] = std::move(tower);
  return true;
}
bool LevelManager::removeTower(int x, int y)
{
  if (x < 0 || y < 0 || x >= width_ || y >= height_ || !towers_[y][x])
    return false;
  towers_[y][x].reset();
  return true;
}
Tower *LevelManager::getTower(int x, int y) const
{
  if (x < 0 || y < 0 || x >= width_ || y >= height_)
    return nullptr;
  return towers_[y][x].get();
}
const Path &LevelManager::getPath() const { return path_; }
WaveManager &LevelManager::getWaveManager() { return waveManager_; }
void LevelManager::reset()
{
  for (int y = 0; y < height_; ++y)
    for (int x = 0; x < width_; ++x)
      towers_[y][x].reset();
  // TODO: Add proper WaveManager reset logic if needed
}