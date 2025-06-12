#pragma once
#include <SFML/Graphics.hpp>
#include "../models/LevelManager.h"
#include "../models/Player.h"

class HUDView
{
public:
  HUDView(unsigned int width, unsigned int tileSize);
  void render(sf::RenderWindow &window, const Player &player, const LevelManager &level) const;

private:
  unsigned int m_width;
  unsigned int m_tileSize;
  sf::Texture m_coinTexture;
  bool m_coinTextureLoaded = false;
  sf::Texture m_heartTexture;
  bool m_heartTextureLoaded = false;
  void drawCoin(sf::RenderWindow &window, float x, float y) const;
  void drawHeart(sf::RenderWindow &window, float x, float y) const;
  void drawWaveBar(sf::RenderWindow &window, float x, float y, int currentWave, int totalWaves) const;
};