#pragma once
#include <SFML/Graphics.hpp>
#include "../models/LevelManager.h"

class LevelView
{
public:
  explicit LevelView(unsigned int tileSize = 64);
  void render(sf::RenderWindow &window, const LevelManager &level) const;
  unsigned int getTileSize() const { return m_tileSize; }

private:
  unsigned int m_tileSize;
};