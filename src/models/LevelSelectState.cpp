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
  int choice;
  std::cin >> choice;
  // manager.setCurrentLevel(choice - 1); // If you have this method
  manager.setState(std::make_unique<TowerPlacementState>());
}

void LevelSelectState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting LevelSelectState\n";
}