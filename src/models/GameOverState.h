#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:
  GameOverState() noexcept;
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) override;
  // Handles game over menu option selection for both text and SFML UI
  void onGameOverOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight);
};