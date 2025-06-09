#pragma once
#include <vector>
#include <memory>
#include "LevelManager.h"

class GameManager
{
public:
  GameManager();
  void addLevel(std::unique_ptr<LevelManager> level);
  LevelManager *getCurrentLevel();
  bool nextLevel();
  bool hasNextLevel() const;
  void resetCurrentLevel();
  int getCurrentLevelIndex() const;
  int getTotalLevels() const;

private:
  std::vector<std::unique_ptr<LevelManager>> levels_;
  int currentLevelIndex_;
};