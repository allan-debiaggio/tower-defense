#include "PlayingState.h"
#include "GameManager.h"
#include <iostream>

void PlayingState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PlayingState\n";
}

void PlayingState::update(GameManager &manager, float dt)
{
  std::cout << "[STATE] PlayingState update (dt=" << dt << ")\n";
  // TODO: Add main game update logic here
}

void PlayingState::handleInput(GameManager &manager)
{
  std::cout << "[STATE] PlayingState handleInput\n";
  // TODO: Add input handling logic here
}

void PlayingState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PlayingState\n";
}