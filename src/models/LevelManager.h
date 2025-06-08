#pragma once
#include <vector>
#include <memory>
#include "Path.h"
#include "Tower.h"
#include "WaveManager.h"

class LevelManager
{
public:
  LevelManager(int width, int height, const Path &path, int numWaves, int enemiesPerWave);
  LevelManager(const LevelManager &) = delete;
  LevelManager &operator=(const LevelManager &) = delete;
  int getWidth() const;
  int getHeight() const;
  bool isBuildable(int x, int y) const;
  bool placeTower(int x, int y, std::unique_ptr<Tower> tower);
  bool removeTower(int x, int y);
  Tower *getTower(int x, int y) const;
  const Path &getPath() const;
  WaveManager &getWaveManager();
  void reset();

private:
  int width_;
  int height_;
  std::vector<std::vector<int>> map_; // 0: empty, 1: path, 2: buildable
  std::vector<std::vector<std::unique_ptr<Tower>>> towers_;
  Path path_;
  WaveManager waveManager_;
};