#pragma once
#include <SFML/Graphics.hpp>
#include "../models/LevelManager.h"

class TowerView
{
public:
  explicit TowerView(unsigned int tileSize = 64);
  void render(sf::RenderWindow &window, const LevelManager &level) const;

private:
  unsigned int m_tileSize;
  // Mario crown icon for upgrades
  mutable sf::Texture m_crownTexture;
  mutable bool m_crownTextureLoaded = false;
};