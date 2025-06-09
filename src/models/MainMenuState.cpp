#include "MainMenuState.h"
#include "GameManager.h"
#include "LevelSelectState.h"
#include <iostream>
#include <memory>

void MainMenuState::enter(GameManager &manager)
{
  std::cout << "\n=== Tower Defense Main Menu ===\n";
  std::cout << "1. New Game\n2. Quit\n";
}

void MainMenuState::update(GameManager &manager, float dt)
{
  // No-op for menu
}

void MainMenuState::handleInput(GameManager &manager)
{
  int choice;
  std::cin >> choice;
  if (choice == 1)
  {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    manager.setPlayerName(name);
    manager.resetPlayer(); // Reset player resources for new game
    std::cout << "Welcome, " << manager.getPlayerName() << "!\n";
    manager.setState(std::make_unique<LevelSelectState>());
  }
  else
  {
    std::cout << "Goodbye!\n";
    // Do not exit, just return
  }
}

void MainMenuState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting MainMenuState\n";
}