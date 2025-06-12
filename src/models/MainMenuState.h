#pragma once
#include "GameState.h"
#include "../views/MainMenuView.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MainMenuState : public GameState
{
public:
  enum class MenuMode
  {
    Main,
    NameEntry,
    LevelSelect
  };
  MainMenuState();
  MainMenuState(unsigned int width, unsigned int height);
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  // Handles menu option selection for both text and SFML UI
  void onMenuOptionSelected(GameManager &manager, int option, const std::string &name = "");
  // SFML event handler for UI navigation
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager);
  // Draws the menu
  void draw(sf::RenderWindow &window);

private:
  void switchMode(MenuMode mode);
  void handleLevelSelected(GameManager &manager, int levelIdx);
  MainMenuView m_menuView;
  MenuMode m_mode = MenuMode::Main;
  bool m_waitingForName = false;
  int m_selectedLevel = -1;
  std::vector<std::string> m_levelNames = {"Level 1", "Level 2", "Level 3"};
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;
};