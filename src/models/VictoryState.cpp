#include "VictoryState.h"
#include "GameManager.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>
#include <memory>

VictoryState::VictoryState() noexcept = default;

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

void VictoryState::onVictoryOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight)
{
  if (option == 1)
  {
    if (manager.nextLevel())
    {
      std::cout << "Starting next level!\n";
      manager.setState(std::make_unique<PlayingState>(windowWidth, windowHeight));
    }
    else
    {
      std::cout << "No more levels! Returning to main menu.\n";
      manager.setState(std::make_unique<MainMenuState>(windowWidth, windowHeight));
    }
  }
  else if (option == 2)
  {
    manager.setState(std::make_unique<MainMenuState>(windowWidth, windowHeight));
  }
  else
  {
    std::cout << "Invalid choice.\n";
  }
}

void VictoryState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice != 1 && choice != 2)
  {
    std::cout << "Select option: ";
    std::cin >> choice;
    onVictoryOptionSelected(manager, choice, 800, 600);
  }
}

void VictoryState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting VictoryState\n";
}

void VictoryState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) {}