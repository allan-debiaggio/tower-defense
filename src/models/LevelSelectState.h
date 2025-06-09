#pragma once
#include "GameState.h"

class LevelSelectState : public GameState
{
public:
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
};