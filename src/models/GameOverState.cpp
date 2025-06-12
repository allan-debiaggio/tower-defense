#include "GameOverState.h"
#include "GameManager.h"
#include "MainMenuState.h"
#include <iostream>
#include <memory>

GameOverState::GameOverState() noexcept = default;

void GameOverState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering GameOverState\n";
  std::cout << "Game Over!\n";
  std::cout << "1. Replay\n2. Quit to Main Menu\n";
}

void GameOverState::update(GameManager &manager, float dt)
{
  // No-op
}

void GameOverState::onGameOverOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight)
{
  if (option == 1)
  {
    // For SFML, go to main menu for new game/level selection
    manager.setState(std::make_unique<MainMenuState>(windowWidth, windowHeight));
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

void GameOverState::handleInput(GameManager &manager)
{
  int choice = 0;
  while (choice != 1 && choice != 2)
  {
    std::cout << "Select option: ";
    std::cin >> choice;
    onGameOverOptionSelected(manager, choice, 800, 600);
  }
}

void GameOverState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting GameOverState\n";
}

void GameOverState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) {}