#pragma once
#include <SFML/Graphics.hpp>
#include "LevelView.h"
#include "TowerView.h"
#include "EnemyView.h"
#include "../models/LevelManager.h"

class GameView
{
public:
  explicit GameView(unsigned int tileSize = 64);
  void render(sf::RenderWindow &window, const LevelManager &level) const;

private:
  LevelView m_levelView;
  TowerView m_towerView;
  EnemyView m_enemyView;
};