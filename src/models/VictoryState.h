#pragma once
#include "GameState.h"
#include "../views/VictoryView.h"
#include <memory>
#include <SFML/Graphics.hpp>

class VictoryState : public GameState
{
public:
  enum class Mode
  {
    NextLevel,
    FinalVictory
  };
  VictoryState(unsigned int windowWidth, unsigned int windowHeight, Mode mode = Mode::NextLevel);
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) override;
  void draw(sf::RenderWindow &window) override;
  // Handles victory menu option selection for both text and SFML UI
  void onVictoryOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight);

private:
  std::unique_ptr<VictoryView> m_view;
  unsigned int m_windowWidth, m_windowHeight;
  Mode m_mode;
  float m_timer = 0.f;
  bool m_transitioned = false;
};