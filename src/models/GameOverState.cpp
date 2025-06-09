#include "GameOverState.h"
#include "GameManager.h"
#include <iostream>

void GameOverState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering GameOverState\n";
}

void GameOverState::update(GameManager &manager, float dt)
{
  std::cout << "[STATE] GameOverState update (dt=" << dt << ")\n";
  // TODO: Add game over logic here
}

void GameOverState::handleInput(GameManager &manager)
{
  std::cout << "[STATE] GameOverState handleInput\n";
  // TODO: Add input handling logic here
}

void GameOverState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting GameOverState\n";
}