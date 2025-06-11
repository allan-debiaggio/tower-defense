#include "GameView.h"

GameView::GameView(unsigned int tileSize)
    : m_levelView(tileSize) {}

void GameView::render(sf::RenderWindow &window, const LevelManager &level) const
{
  m_levelView.render(window, level);
}