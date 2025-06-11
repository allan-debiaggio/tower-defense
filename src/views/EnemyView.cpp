#include "EnemyView.h"

EnemyView::EnemyView(unsigned int tileSize)
    : m_tileSize(tileSize) {}

void EnemyView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  const auto &waveManager = level.getWaveManager();
  const auto &enemies = waveManager.getActiveEnemies();
  for (const auto &enemyPtr : enemies)
  {
    if (enemyPtr && enemyPtr->isAlive())
    {
      auto [ex, ey] = enemyPtr->getPosition();
      sf::CircleShape shape(m_tileSize * 0.28f);
      shape.setFillColor(sf::Color(220, 60, 60)); // Red for enemies
      shape.setOrigin(sf::Vector2f(m_tileSize * 0.28f, m_tileSize * 0.28f));
      shape.setPosition(sf::Vector2f((ex + 0.5f) * m_tileSize, (ey + 0.5f) * m_tileSize));
      window.draw(shape);
    }
  }
}