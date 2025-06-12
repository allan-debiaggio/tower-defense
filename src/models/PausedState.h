#pragma once
#include "GameState.h"

class PausedState : public GameState
{
public:
  PausedState() noexcept;
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) override;
  // Handles pause menu option selection for both text and SFML UI
  void onPauseOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight);
};