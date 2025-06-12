#pragma once

class GameManager; // Forward declaration
#include <SFML/Graphics.hpp>

class GameState
{
public:
  virtual ~GameState() = default;
  virtual void enter(GameManager &manager) {}
  virtual void update(GameManager &manager, float dt) = 0;
  virtual void handleInput(GameManager &manager) {}
  virtual void exit(GameManager &manager) {}
  // SFML event handler
  virtual void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) {}
  // SFML draw method
  virtual void draw(sf::RenderWindow &window) {}
};