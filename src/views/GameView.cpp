#include "GameView.h"

GameView::GameView(unsigned int tileSize)
    : m_levelView(tileSize), m_towerView(tileSize), m_enemyView(tileSize) {}

void GameView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  m_levelView.render(window, level);
  m_towerView.render(window, level);
  m_enemyView.render(window, level);
}

void GameView::renderProjectiles(sf::RenderWindow &window, const std::list<std::unique_ptr<Projectile>> &projectiles) const
{
  for (const auto &proj : projectiles)
  {
    auto [px, py] = proj->getPosition();
    sf::CircleShape shape(12.0f); // 24px diameter
    if (dynamic_cast<const FireballProjectile *>(proj.get()))
    {
      shape.setFillColor(sf::Color(255, 80, 40)); // Red/orange for fireball
    }
    else if (dynamic_cast<const IceProjectile *>(proj.get()))
    {
      shape.setFillColor(sf::Color(80, 180, 255)); // Blue for ice
    }
    else
    {
      shape.setFillColor(sf::Color(180, 180, 180)); // Gray for unknown
    }
    shape.setOrigin(sf::Vector2f(12.0f, 12.0f));
    shape.setPosition(sf::Vector2f(
        px * m_levelView.getTileSize() + m_levelView.getTileSize() / 2,
        py * m_levelView.getTileSize() + m_levelView.getTileSize() / 2));
    window.draw(shape);
  }
}