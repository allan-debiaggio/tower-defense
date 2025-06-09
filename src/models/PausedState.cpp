#include "PausedState.h"
#include "GameManager.h"
#include <iostream>

void PausedState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PausedState\n";
}

void PausedState::update(GameManager &manager, float dt)
{
  std::cout << "[STATE] PausedState update (dt=" << dt << ")\n";
  // No game logic while paused
}

void PausedState::handleInput(GameManager &manager)
{
  std::cout << "[STATE] PausedState handleInput\n";
  // TODO: Add input handling logic here
}

void PausedState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PausedState\n";
}