#include "LevelView.h"
#include <SFML/System/Angle.hpp>

LevelView::LevelView(unsigned int tileSize)
    : m_tileSize(tileSize) {}

void LevelView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  unsigned int width = level.getWidth();
  unsigned int height = level.getHeight();
  for (unsigned int y = 0; y < height; ++y)
  {
    for (unsigned int x = 0; x < width; ++x)
    {
      sf::RectangleShape cell(sf::Vector2f(m_tileSize - 2, m_tileSize - 2));
      cell.setPosition(sf::Vector2f(x * m_tileSize + 1, y * m_tileSize + 1));
      int mapValue = level.getMapValue(x, y);
      if (mapValue == 1)
      {
        cell.setFillColor(sf::Color(255, 220, 40)); // Yellow for path (waypoint tile)
      }
      else if (level.isBuildable(x, y))
      {
        cell.setFillColor(sf::Color(60, 180, 75)); // Green for buildable
      }
      else
      {
        cell.setFillColor(sf::Color(200, 200, 200)); // Gray for blocked
      }
      window.draw(cell);
    }
  }
  // Draw continuous path (road) between waypoints
  sf::Color roadColor(255, 220, 40);
  float roadWidth = m_tileSize * 0.6f;
  for (const auto &path : level.getPaths())
  {
    size_t n = path.getNumWaypoints();
    if (n < 2)
      continue;
    for (size_t i = 0; i < n - 1; ++i)
    {
      auto [x1, y1] = path.getWaypoint(i);
      auto [x2, y2] = path.getWaypoint(i + 1);
      sf::Vector2f p1((x1 + 0.5f) * m_tileSize, (y1 + 0.5f) * m_tileSize);
      sf::Vector2f p2((x2 + 0.5f) * m_tileSize, (y2 + 0.5f) * m_tileSize);
      sf::Vector2f dir = p2 - p1;
      float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
      float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;
      sf::RectangleShape road(sf::Vector2f(length, roadWidth));
      road.setOrigin(sf::Vector2f(0, roadWidth / 2));
      road.setPosition(p1);
      road.setRotation(sf::degrees(angle));
      road.setFillColor(roadColor);
      window.draw(road);
    }
  }
}