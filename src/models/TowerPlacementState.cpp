#include "TowerPlacementState.h"
#include "GameManager.h"
#include "PlayingState.h"
#include "Tower.h"
#include <iostream>
#include <memory>

void TowerPlacementState::enter(GameManager &manager)
{
  std::cout << "\n=== Tower Placement ===\n";
  std::cout << "You have " << manager.getPlayer().getCoins() << " coins.\n";
  std::cout << "Available towers: 1. FireFlower (10 coins), 2. IceTower (10 coins)\n";
  std::cout << "Enter 0 to finish placement.\n";
}

void TowerPlacementState::update(GameManager &manager, float dt)
{
  // No-op for placement
}

void TowerPlacementState::handleInput(GameManager &manager)
{
  int choice = -1;
  while (true)
  {
    std::cout << "Place tower (1=FireFlower, 2=IceTower, 0=done): ";
    std::cin >> choice;
    if (choice == 0)
      break;
    if (choice != 1 && choice != 2)
    {
      std::cout << "Invalid tower type.\n";
      continue;
    }
    int x, y;
    std::cout << "Enter x y position: ";
    std::cin >> x >> y;
    if (!manager.getCurrentLevel()->isBuildable(x, y))
    {
      std::cout << "Cannot build at that position.\n";
      continue;
    }
    int cost = 10;
    if (!manager.getPlayer().spendCoins(cost))
    {
      std::cout << "Not enough coins!\n";
      continue;
    }
    std::unique_ptr<Tower> tower;
    if (choice == 1)
      tower = std::make_unique<FireFlowerTower>(std::make_pair((float)x, (float)y));
    else
      tower = std::make_unique<IceTower>(std::make_pair((float)x, (float)y));
    manager.getCurrentLevel()->placeTower(x, y, std::move(tower));
    std::cout << "Tower placed at (" << x << ", " << y << "). Coins left: " << manager.getPlayer().getCoins() << "\n";
  }
  std::cout << "Towers placed! Starting game...\n";
  manager.setState(std::make_unique<PlayingState>());
}

void TowerPlacementState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting TowerPlacementState\n";
}