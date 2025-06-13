#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

class GameOverView
{
public:
  GameOverView(unsigned int width, unsigned int height);
  void draw(sf::RenderWindow &window);
  bool isReturnToMenuClicked(const sf::Vector2i &mousePos) const;
  bool isQuitClicked(const sf::Vector2i &mousePos) const;

private:
  unsigned int m_width, m_height;
  sf::Font m_font;
  sf::Texture m_bowserTexture;
  std::optional<sf::Sprite> m_bowserSprite;
  sf::RectangleShape m_returnButton, m_quitButton;
  std::optional<sf::Text> m_gameOverText, m_returnText, m_quitText;
  void layout();
};