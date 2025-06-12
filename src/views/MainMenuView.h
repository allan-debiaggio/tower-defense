#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <vector>

class MainMenuView
{
public:
  enum class MenuMode
  {
    Main,
    NameEntry,
    LevelSelect
  };
  MainMenuView(unsigned int width, unsigned int height);
  void draw(sf::RenderWindow &window);
  bool isNewGameClicked(const sf::Vector2i &mousePos) const;
  bool isQuitClicked(const sf::Vector2i &mousePos) const;
  void showNameInput(bool show);
  bool isNameInputActive() const;
  void handleTextInput(const sf::Event &event);
  std::string getPlayerName() const;
  unsigned int getWidth() const { return m_width; }
  unsigned int getHeight() const { return m_height; }

  // Level selection UI
  void setMode(MenuMode mode);
  MenuMode getMode() const;
  void setLevelNames(const std::vector<std::string> &names);
  int getLevelClicked(const sf::Vector2i &mousePos) const;

private:
  void drawLevelSelection(sf::RenderWindow &window);
  unsigned int m_width, m_height;
  sf::Font m_font;
  sf::Texture m_marioTexture, m_peachTexture, m_bowserTexture, m_goombaTexture;
  std::optional<sf::Sprite> m_marioSprite, m_peachSprite, m_bowserSprite, m_goombaSprite;
  sf::RectangleShape m_newGameButton, m_quitButton;
  std::optional<sf::Text> m_title, m_newGameText, m_quitText;
  // Name input popup
  bool m_showNameInput = false;
  sf::RectangleShape m_nameInputBox;
  std::optional<sf::Text> m_nameInputPrompt, m_nameInputText;
  std::string m_playerName;
  // Level selection
  MenuMode m_mode = MenuMode::Main;
  std::vector<std::string> m_levelNames;
  std::vector<sf::RectangleShape> m_levelButtons;
};