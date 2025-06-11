#include "LevelView.h"

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
      if (level.isBuildable(x, y))
      {
        cell.setFillColor(sf::Color(60, 180, 75)); // Green for buildable
      }
      else
      {
        cell.setFillColor(sf::Color(200, 200, 200)); // Gray for path or blocked
      }
      window.draw(cell);
    }
  }
}