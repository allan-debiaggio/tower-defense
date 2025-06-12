#pragma once
#include <SFML/Graphics.hpp>
#include "LevelView.h"
#include "TowerView.h"
#include "EnemyView.h"
#include "../models/LevelManager.h"
#include "../models/Projectile.h"
#include <list>

class GameView
{
public:
  explicit GameView(unsigned int tileSize = 64);
  void render(sf::RenderWindow &window, const LevelManager &level) const;
  void renderProjectiles(sf::RenderWindow &window, const std::list<std::unique_ptr<Projectile>> &projectiles) const;

private:
  LevelView m_levelView;
  TowerView m_towerView;
  EnemyView m_enemyView;
};