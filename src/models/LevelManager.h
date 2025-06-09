#pragma once
#include <vector>
#include <memory>
#include "Path.h"
#include "Tower.h"
#include "WaveManager.h"
#include <random>

class LevelManager
{
public:
  LevelManager(int width, int height, const std::vector<Path> &paths, int numWaves, int enemiesPerWave);
  LevelManager(const LevelManager &) = delete;
  LevelManager &operator=(const LevelManager &) = delete;
  int getWidth() const;
  int getHeight() const;
  bool isBuildable(int x, int y) const;
  bool placeTower(int x, int y, std::unique_ptr<Tower> tower);
  bool removeTower(int x, int y);
  Tower *getTower(int x, int y) const;
  const std::vector<Path> &getPaths() const;
  const Path &getPath(size_t index) const;
  size_t getNumPaths() const;
  WaveManager &getWaveManager();
  void reset();

private:
  int width_;
  int height_;
  std::vector<std::vector<int>> map_; // 0: empty, 1: path, 2: buildable
  std::vector<std::vector<std::unique_ptr<Tower>>> towers_;
  std::vector<Path> paths_;
  WaveManager waveManager_;
};