#pragma once
#include "GameState.h"

class PlayingState : public GameState
{
public:
  PlayingState();
  PlayingState(unsigned int windowWidth, unsigned int windowHeight);
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;

private:
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;
};