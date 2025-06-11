#include <SFML/Graphics.hpp>
#include "src/models/LevelManager.h"
#include <memory>
#include "src/views/GameView.h"

int main()
{
  // Example level setup (10x5 grid, as in main.cpp)
  std::vector<std::pair<float, float>> waypoints = {{0, 2}, {5, 2}, {9, 2}};
  Path path(waypoints);
  std::vector<Path> paths = {path};
  int numWaves = 1;
  int enemiesPerWave = 2;
  std::unique_ptr<LevelManager> level = std::make_unique<LevelManager>(10, 5, paths, numWaves, enemiesPerWave);

  const unsigned int tileSize = 64;
  unsigned int width = level->getWidth();
  unsigned int height = level->getHeight();
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width * tileSize, height * tileSize)), "Tower Defense - SFML");

  GameView gameView(tileSize);

  while (window.isOpen())
  {
    while (auto eventOpt = window.pollEvent())
    {
      const sf::Event &event = *eventOpt;
      if (event.is<sf::Event::Closed>())
        window.close();
    }
    window.clear(sf::Color::Black);
    gameView.render(window, *level);
    window.display();
  }
  return 0;
}