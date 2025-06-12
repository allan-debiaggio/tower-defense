#include "TowerView.h"

TowerView::TowerView(unsigned int tileSize)
    : m_tileSize(tileSize)
{
  if (m_crownTexture.loadFromFile("assets/ui_crown.png"))
    m_crownTextureLoaded = true;
}

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
        // Draw crowns for upgrades
        int level = tower->getLevel();
        if (m_crownTextureLoaded && level > 1)
        {
          int numCrowns = std::min(std::max(level - 1, 1), 3); // Only 1-3 crowns
          float iconSize = m_tileSize * 0.28f;
          float spacing = iconSize * 1.1f;
          float totalWidth = spacing * (numCrowns - 1);
          float baseX = (x + 0.5f) * m_tileSize - totalWidth / 2.0f;
          float yCrown = (y + 0.5f) * m_tileSize - m_tileSize * 0.48f;
          for (int i = 0; i < numCrowns; ++i)
          {
            sf::Sprite crown(m_crownTexture);
            crown.setScale(sf::Vector2f(iconSize / m_crownTexture.getSize().x, iconSize / m_crownTexture.getSize().y));
            crown.setPosition(sf::Vector2f(baseX + i * spacing, yCrown));
            window.draw(crown);
          }
        }
      }
    }
  }
}