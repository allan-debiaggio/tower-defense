#pragma once
#include "GameState.h"
#include "../views/GameOverView.h"
#include <memory>
#include <SFML/Graphics.hpp>

class GameOverState : public GameState
{
public:
  GameOverState(unsigned int windowWidth, unsigned int windowHeight);
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) override;
  void draw(sf::RenderWindow &window) override;
  // Handles game over menu option selection for both text and SFML UI
  void onGameOverOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight);

private:
  std::unique_ptr<GameOverView> m_view;
  unsigned int m_windowWidth, m_windowHeight;
};