#include "PlayingState.h"
#include "GameManager.h"
#include "PausedState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include <iostream>
#include <memory>

void PlayingState::enter(GameManager &manager)
{
  std::cout << "[STATE] Entering PlayingState\n";
}

void PlayingState::update(GameManager &manager, float dt)
{
  auto &level = *manager.getCurrentLevel();
  auto &waveManager = level.getWaveManager();
  auto &player = manager.getPlayer();

  // Update wave/enemy logic
  waveManager.update(dt);

  // Simulate enemies reaching the end (for demonstration)
  // In a real game, check enemy positions and reduce lives if needed
  // For now, just print player stats
  std::cout << "Player: " << manager.getPlayerName() << " | Coins: " << player.getCoins() << " | Lives: " << player.getLives() << "\n";
  std::cout << "Current Wave: " << waveManager.getCurrentWave() << "\n";

  // Check for defeat
  if (player.getLives() <= 0)
  {
    std::cout << "You lost all your lives!\n";
    manager.setState(std::make_unique<GameOverState>());
    return;
  }
  // Check for victory
  if (!waveManager.hasNextWave() && !waveManager.isWaveActive())
  {
    std::cout << "All waves cleared!\n";
    manager.setState(std::make_unique<VictoryState>());
    return;
  }
}

void PlayingState::handleInput(GameManager &manager)
{
  std::cout << "Press p to pause, q to quit, or Enter to continue: ";
  std::string input;
  std::getline(std::cin, input);
  if (input == "p")
  {
    manager.setState(std::make_unique<PausedState>());
  }
  else if (input == "q")
  {
    manager.setState(std::make_unique<GameOverState>());
  }
  // Otherwise, continue playing
}

void PlayingState::exit(GameManager &manager)
{
  std::cout << "[STATE] Exiting PlayingState\n";
}