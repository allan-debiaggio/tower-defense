#include <SFML/Graphics.hpp>
#include "src/models/GameManager.h"
#include "src/models/MainMenuState.h"
#include <memory>
#include <iostream>

int main()
{
  const unsigned int windowWidth = 1024;
  const unsigned int windowHeight = 768;
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Super Mario Tower Defense - SFML");

  GameManager manager;
  manager.setState(std::make_unique<MainMenuState>(windowWidth, windowHeight));

  sf::Clock clock;
  while (window.isOpen())
  {
    while (auto eventOpt = window.pollEvent())
    {
      const sf::Event &event = *eventOpt;
      if (event.is<sf::Event::Closed>())
        window.close();
      manager.handleEvent(event, window);
    }
    float dt = clock.restart().asSeconds();
    dt = std::min(dt, 0.05f);
    manager.update(dt);
    window.clear(sf::Color::Black);
    manager.draw(window);
    window.display();
  }
  return 0;
}