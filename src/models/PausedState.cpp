#include "PausedState.h"
#include "GameManager.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include <iostream>
#include <memory>

void PausedState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PausedState\n";
  std::cout << "Game paused.\n";
  std::cout << "1. Resume\n2. Quit to Main Menu\n";
}

void PausedState::update(GameManager &manager, float dt)
{
  std::cout << "[STATE] PausedState update (dt=" << dt << ")\n";
  // No game logic while paused
}

void PausedState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice != 1 && choice != 2)
  {
    std::cout << "Select option: ";
    std::cin >> choice;
    if (choice == 1)
    {
      manager.setState(std::make_unique<PlayingState>());
    }
    else if (choice == 2)
    {
      manager.setState(std::make_unique<MainMenuState>());
    }
    else
    {
      std::cout << "Invalid choice.\n";
    }
  }
}

void PausedState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PausedState\n";
}