#pragma once
#include <SFML/Graphics.hpp>
#include "../models/LevelManager.h"

class LevelView
{
public:
  explicit LevelView(unsigned int tileSize = 64);
  void render(sf::RenderWindow &window, const LevelManager &level) const;

private:
  unsigned int m_tileSize;
};