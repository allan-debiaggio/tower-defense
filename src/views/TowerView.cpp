#include "TowerView.h"

TowerView::TowerView(unsigned int tileSize)
    : m_tileSize(tileSize) {}

void TowerView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  unsigned int width = level.getWidth();
  unsigned int height = level.getHeight();
  for (unsigned int y = 0; y < height; ++y)
  {
    for (unsigned int x = 0; x < width; ++x)
    {
      const Tower *tower = level.getTower(x, y);
      if (tower)
      {
        sf::CircleShape shape(m_tileSize * 0.35f);
        shape.setFillColor(sf::Color(60, 120, 255)); // Blue for towers
        shape.setOrigin(sf::Vector2f(m_tileSize * 0.35f, m_tileSize * 0.35f));
        shape.setPosition(sf::Vector2f((x + 0.5f) * m_tileSize, (y + 0.5f) * m_tileSize));
        window.draw(shape);
      }
    }
  }
}