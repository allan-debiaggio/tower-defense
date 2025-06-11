#include <SFML/Graphics.hpp>
#include "src/models/LevelManager.h"
#include <memory>
#include <variant>

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

  while (window.isOpen())
  {
    while (auto eventOpt = window.pollEvent())
    {
      const sf::Event &event = *eventOpt;
      if (event.is<sf::Event::Closed>())
        window.close();
    }
    window.clear(sf::Color::Black);
    // Draw grid
    for (unsigned int y = 0; y < height; ++y)
    {
      for (unsigned int x = 0; x < width; ++x)
      {
        sf::RectangleShape cell(sf::Vector2f(tileSize - 2, tileSize - 2));
        cell.setPosition(sf::Vector2f(x * tileSize + 1, y * tileSize + 1));
        if (level->isBuildable(x, y))
          cell.setFillColor(sf::Color(60, 180, 75)); // Green for buildable
        else
          cell.setFillColor(sf::Color(200, 200, 200)); // Gray for path or blocked
        window.draw(cell);
      }
    }
    window.display();
  }
  return 0;
}