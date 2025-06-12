#include "PausedState.h"
#include "GameManager.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include <iostream>
#include <memory>

PausedState::PausedState() noexcept = default;

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

void PausedState::onPauseOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight)
{
  if (option == 1)
  {
    manager.setState(std::make_unique<PlayingState>(windowWidth, windowHeight));
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

void PausedState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice != 1 && choice != 2)
  {
    std::cout << "Select option: ";
    std::cin >> choice;
    onPauseOptionSelected(manager, choice, 0, 0);
  }
}

void PausedState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PausedState\n";
}

void PausedState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) {}