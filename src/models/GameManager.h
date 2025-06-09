#pragma once
#include <vector>
#include <memory>
#include "LevelManager.h"
#include "GameState.h"

class PlayingState;
class PausedState;
class GameOverState;
class VictoryState;

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
  void setState(std::unique_ptr<GameState> newState);
  void update(float dt);
  void handleInput();

private:
  std::vector<std::unique_ptr<LevelManager>> levels_;
  int currentLevelIndex_;
  std::unique_ptr<GameState> currentState_;
};