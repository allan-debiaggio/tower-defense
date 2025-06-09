#include "TowerPlacementState.h"
#include "GameManager.h"
#include "PlayingState.h"
#include <iostream>
#include <memory>

void TowerPlacementState::enter(GameManager &manager)
{
  std::cout << "\n=== Tower Placement ===\n";
  std::cout << "Place your towers on the map. (Simulated for test)\n";
  // In a real game, you would prompt for coordinates and tower type
}

void TowerPlacementState::update(GameManager &manager, float dt)
{
  // No-op for placement
}

void TowerPlacementState::handleInput(GameManager &manager)
{
  std::cout << "Towers placed! Starting game...\n";
  manager.setState(std::make_unique<PlayingState>());
}

void TowerPlacementState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting TowerPlacementState\n";
}