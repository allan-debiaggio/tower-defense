#include "GameOverState.h"
#include "GameManager.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>
#include <memory>

GameOverState::GameOverState(unsigned int windowWidth, unsigned int windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{
  m_view = std::make_unique<GameOverView>(windowWidth, windowHeight);
}

void GameOverState::enter(GameManager &manager)
{
  // No-op for SFML
}

void GameOverState::update(GameManager &manager, float dt)
{
  // No-op for SFML
}

void GameOverState::draw(sf::RenderWindow &window)
{
  if (m_view)
    m_view->draw(window);
}

void GameOverState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager)
{
  if (event.is<sf::Event::MouseButtonPressed>())
  {
    const auto *mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
    if (mouseEvent)
    {
      sf::Vector2i pos(mouseEvent->position.x, mouseEvent->position.y);
      if (m_view->isReturnToMenuClicked(pos))
      {
        manager.setState(std::make_unique<MainMenuState>(m_windowWidth, m_windowHeight));
      }
      else if (m_view->isQuitClicked(pos))
      {
        window.close();
      }
    }
  }
}

void GameOverState::onGameOverOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight)
{
  // Not used in SFML
}

void GameOverState::handleInput(GameManager &manager)
{
  // Not used in SFML
}

void GameOverState::exit(GameManager &manager)
{
  // No-op for SFML
}