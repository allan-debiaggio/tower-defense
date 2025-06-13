#include "MainMenuState.h"
#include "GameManager.h"
#include "LevelSelectState.h"
#include "PlayingState.h"
#include <iostream>
#include <memory>

MainMenuState::MainMenuState() : m_menuView(800, 600), m_windowWidth(800), m_windowHeight(600)
{
  m_menuView.setLevelNames(m_levelNames);
}

MainMenuState::MainMenuState(unsigned int width, unsigned int height)
    : m_menuView(width, height), m_windowWidth(width), m_windowHeight(height)
{
  m_menuView.setLevelNames(m_levelNames);
}

void MainMenuState::enter(GameManager &manager)
{
  m_mode = MenuMode::Main;
  m_menuView.setMode(MainMenuView::MenuMode::Main);
  m_waitingForName = false;
  m_menuView.showNameInput(false);
}

void MainMenuState::update(GameManager &manager, float dt)
{
  // No-op for menu
}

void MainMenuState::onMenuOptionSelected(GameManager &manager, int option, const std::string &name)
{
  std::cout << "[DEBUG] onMenuOptionSelected: option=" << option << ", mode=" << static_cast<int>(m_mode) << ", name='" << name << "'\n";
  if (option == 1) // New Game
  {
    m_menuView.showNameInput(true);
    m_mode = MenuMode::NameEntry;
    std::cout << "[DEBUG] Switched to NameEntry mode" << std::endl;
  }
  else if (option == 2) // Quit
  {
    // ... existing code ...
  }
}

void MainMenuState::handleInput(GameManager &manager)
{
  // Not used in SFML
}

void MainMenuState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager)
{
  std::cout << "[DEBUG] handleEvent: mode=" << static_cast<int>(m_mode) << std::endl;
  if (m_mode == MenuMode::NameEntry && m_menuView.isNameInputActive())
  {
    m_menuView.handleTextInput(event);
    if (const auto *textEvent = event.getIf<sf::Event::TextEntered>())
    {
      std::cout << "[DEBUG] TextEntered event: unicode=" << textEvent->unicode << ", char='" << static_cast<char>(textEvent->unicode) << "'" << std::endl;
      if (textEvent->unicode == 13)
      {
        std::string name = m_menuView.getPlayerName();
        std::cout << "[DEBUG] Enter pressed, name='" << name << "'" << std::endl;
        m_menuView.showNameInput(false);
        m_waitingForName = false;
        if (!name.empty())
        {
          std::cout << "[DEBUG] Name is not empty, calling switchMode(LevelSelect)" << std::endl;
          manager.setPlayerName(name);
          switchMode(MenuMode::LevelSelect);
          std::cout << "[DEBUG] Switched to LevelSelect mode after name entry" << std::endl;
        }
        else
        {
          std::cout << "[DEBUG] Name is empty, popup remains open" << std::endl;
        }
      }
    }
    // --- Handle Enter/Return in KeyPressed events for macOS and cross-platform reliability ---
    if (const auto *keyEvent = event.getIf<sf::Event::KeyPressed>())
    {
      if (keyEvent->scancode == sf::Keyboard::Scancode::Enter)
      {
        std::string name = m_menuView.getPlayerName();
        std::cout << "[DEBUG] KeyPressed Enter (SFML3), name='" << name << "'" << std::endl;
        m_menuView.showNameInput(false);
        m_waitingForName = false;
        if (!name.empty())
        {
          std::cout << "[DEBUG] Name is not empty, calling switchMode(LevelSelect) (KeyPressed, SFML3)" << std::endl;
          manager.setPlayerName(name);
          switchMode(MenuMode::LevelSelect);
          std::cout << "[DEBUG] Switched to LevelSelect mode after name entry (KeyPressed, SFML3)" << std::endl;
        }
        else
        {
          std::cout << "[DEBUG] Name is empty, popup remains open (KeyPressed, SFML3)" << std::endl;
        }
      }
    }
    return;
  }
  if (event.is<sf::Event::MouseButtonPressed>())
  {
    if (const auto *mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
      auto pos = sf::Vector2i(mouseEvent->position.x, mouseEvent->position.y);
      std::cout << "[DEBUG] Mouse click at " << pos.x << ", " << pos.y << std::endl;
      if (m_mode == MenuMode::Main)
      {
        std::cout << "[DEBUG] In Main mode, checking buttons..." << std::endl;
        if (m_menuView.isNewGameClicked(pos))
        {
          std::cout << "[DEBUG] New Game button clicked" << std::endl;
          onMenuOptionSelected(manager, 1);
        }
        else if (m_menuView.isQuitClicked(pos))
        {
          std::cout << "[DEBUG] Quit button clicked" << std::endl;
          onMenuOptionSelected(manager, 2);
          window.close();
        }
      }
      else if (m_mode == MenuMode::LevelSelect)
      {
        int levelIdx = m_menuView.getLevelClicked(pos);
        std::cout << "[DEBUG] LevelSelect mode, getLevelClicked returned " << levelIdx << std::endl;
        if (levelIdx >= 0)
        {
          handleLevelSelected(manager, levelIdx);
        }
      }
    }
    return;
  }
}

void MainMenuState::handleLevelSelected(GameManager &manager, int levelIdx)
{
  m_selectedLevel = levelIdx;
  manager.setCurrentLevelIndex(levelIdx);
  manager.resetCurrentLevel();
  // Reset player for new game/level
  manager.resetPlayer();
  // Transition to PlayingState
  manager.setState(std::make_unique<PlayingState>(m_windowWidth, m_windowHeight));
}

void MainMenuState::draw(sf::RenderWindow &window)
{
  m_menuView.draw(window);
}

void MainMenuState::switchMode(MenuMode mode)
{
  std::cout << "[DEBUG] MainMenuState::switchMode called, mode=" << static_cast<int>(mode) << std::endl;
  m_mode = mode;
  switch (mode)
  {
  case MenuMode::Main:
    m_menuView.setMode(MainMenuView::MenuMode::Main);
    break;
  case MenuMode::NameEntry:
    m_menuView.setMode(MainMenuView::MenuMode::NameEntry);
    break;
  case MenuMode::LevelSelect:
    m_menuView.setMode(MainMenuView::MenuMode::LevelSelect);
    break;
  }
}

void MainMenuState::exit(GameManager &manager)
{
  // No-op for SFML
}