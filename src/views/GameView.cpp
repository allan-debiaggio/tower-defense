#include "GameView.h"

GameView::GameView(unsigned int tileSize)
    : m_levelView(tileSize), m_towerView(tileSize), m_enemyView(tileSize) {}

void GameView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  m_levelView.render(window, level);
  m_towerView.render(window, level);
  m_enemyView.render(window, level);
}