#include "VictoryState.h"
#include "GameManager.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>
#include <memory>

VictoryState::VictoryState(unsigned int windowWidth, unsigned int windowHeight, Mode mode)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_mode(mode)
{
  m_view = std::make_unique<VictoryView>(windowWidth, windowHeight);
  m_view->setMode(static_cast<VictoryView::Mode>(mode));
}

void VictoryState::enter(GameManager &manager)
{
  m_timer = 0.f;
  m_transitioned = false;
}

void VictoryState::update(GameManager &manager, float dt)
{
  if (m_mode == Mode::NextLevel && !m_transitioned)
  {
    m_timer += dt;
    if (m_timer > 2.0f)
    { // 2 seconds delay
      m_transitioned = true;
      if (manager.nextLevel())
      {
        manager.resetCurrentLevel();
        manager.setState(std::make_unique<PlayingState>(m_windowWidth, m_windowHeight));
      }
      else
      {
        manager.setState(std::make_unique<VictoryState>(m_windowWidth, m_windowHeight, Mode::FinalVictory));
      }
    }
  }
}

void VictoryState::draw(sf::RenderWindow &window)
{
  if (m_view)
    m_view->draw(window);
}

void VictoryState::handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager)
{
  if (m_mode == Mode::FinalVictory && event.is<sf::Event::MouseButtonPressed>())
  {
    const auto *mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
    if (mouseEvent)
    {
      sf::Vector2i pos(mouseEvent->position.x, mouseEvent->position.y);
      if (m_view->isReturnToMenuClicked(pos))
      {
        manager.setState(std::make_unique<MainMenuState>(m_windowWidth, m_windowHeight));
      }
    }
  }
}

void VictoryState::onVictoryOptionSelected(GameManager &manager, int option, unsigned int windowWidth, unsigned int windowHeight)
{
  // Not used in SFML
}

void VictoryState::handleInput(GameManager &manager)
{
  // Not used in SFML
}

void VictoryState::exit(GameManager &manager)
{
  // No-op for SFML
}