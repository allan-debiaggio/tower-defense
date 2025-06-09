#include "LevelSelectState.h"
#include "GameManager.h"
#include "TowerPlacementState.h"
#include <iostream>
#include <memory>

void LevelSelectState::enter(GameManager &manager)
{
  std::cout << "\n=== Select Level ===\n";
  std::cout << "1. Level 1\n2. Level 2\n3. Level 3\n";
}

void LevelSelectState::update(GameManager &manager, float dt)
{
  // No-op for menu
}

void LevelSelectState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice < 1 || choice > 3)
  {
    std::cout << "Select a level (1-3): ";
    std::cin >> choice;
    if (choice < 1 || choice > 3)
    {
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
  std::cout << "Level " << choice << " selected.\n";
  manager.setCurrentLevelIndex(choice - 1);
  manager.setState(std::make_unique<TowerPlacementState>());
}

void LevelSelectState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting LevelSelectState\n";
}