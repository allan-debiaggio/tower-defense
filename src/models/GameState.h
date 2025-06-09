#pragma once

class GameManager; // Forward declaration

class GameState
{
public:
  virtual ~GameState() = default;
  virtual void enter(GameManager &manager) {}
  virtual void update(GameManager &manager, float dt) = 0;
  virtual void handleInput(GameManager &manager) {}
  virtual void exit(GameManager &manager) {}
};