#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

class VictoryView
{
public:
  enum class Mode
  {
    NextLevel,
    FinalVictory
  };
  VictoryView(unsigned int width, unsigned int height);
  void draw(sf::RenderWindow &window);
  void setMode(Mode mode);
  bool isReturnToMenuClicked(const sf::Vector2i &mousePos) const;

private:
  unsigned int m_width, m_height;
  sf::Font m_font;
  sf::Texture m_bowserTexture;
  std::optional<sf::Sprite> m_bowserSprite;
  sf::RectangleShape m_returnButton;
  std::optional<sf::Text> m_victoryText;
  std::optional<sf::Text> m_returnText;
  Mode m_mode = Mode::NextLevel;
  void layout();
};