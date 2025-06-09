#include "VictoryState.h"
#include "GameManager.h"
#include <iostream>

void VictoryState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering VictoryState\n";
}

void VictoryState::update(GameManager &manager, float dt)
{
  std::cout << "[STATE] VictoryState update (dt=" << dt << ")\n";
  // TODO: Add victory logic here
}

void VictoryState::handleInput(GameManager &manager)
{
  std::cout << "[STATE] VictoryState handleInput\n";
  // TODO: Add input handling logic here
}

void VictoryState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting VictoryState\n";
}