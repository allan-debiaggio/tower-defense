#include "VictoryState.h"
#include "GameManager.h"
#include "MainMenuState.h"
#include "LevelSelectState.h"
#include <iostream>
#include <memory>

void VictoryState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering VictoryState\n";
  std::cout << "Congratulations! You won!\n";
  std::cout << "1. Next Level\n2. Quit to Main Menu\n";
}

void VictoryState::update(GameManager &manager, float dt)
{
  // No-op
}

void VictoryState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice != 1 && choice != 2)
  {
    std::cout << "Select option: ";
    std::cin >> choice;
    if (choice == 1)
    {
      manager.setState(std::make_unique<LevelSelectState>());
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

void VictoryState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting VictoryState\n";
}