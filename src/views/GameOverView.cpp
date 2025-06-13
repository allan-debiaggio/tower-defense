#include "GameOverView.h"
#include <iostream>

GameOverView::GameOverView(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
  if (!m_font.openFromFile("presentation/assets/PressStart2P.ttf"))
  {
    std::cerr << "[GameOverView] Failed to load font!" << std::endl;
  }
  if (!m_bowserTexture.loadFromFile("presentation/assets/bowser1.png"))
  {
    std::cerr << "[GameOverView] Failed to load bowser1.png!" << std::endl;
  }
  m_bowserSprite.emplace(m_bowserTexture);
  m_gameOverText.emplace(m_font, "Game Over", 48);
  m_gameOverText->setFillColor(sf::Color(230, 57, 70));
  m_gameOverText->setStyle(sf::Text::Bold);
  m_returnText.emplace(m_font, "Return to Menu", 24);
  m_returnText->setFillColor(sf::Color::White);
  m_quitText.emplace(m_font, "Quit", 24);
  m_quitText->setFillColor(sf::Color::White);
  layout();
}

void GameOverView::layout()
{
  float padding = 60.f;
  float returnWidth = m_returnText->getLocalBounds().size.x;
  float quitWidth = m_quitText->getLocalBounds().size.x;
  float buttonWidth = std::max(returnWidth, quitWidth) + padding;
  float buttonHeight = 70.f;
  float spacing = 40.f;
  // Center Bowser image higher
  float bowserScale = std::min((float)m_width / 2.0f / m_bowserTexture.getSize().x, (float)m_height / 2.5f / m_bowserTexture.getSize().y);
  m_bowserSprite->setScale(sf::Vector2f(bowserScale, bowserScale));
  auto bowserBounds = m_bowserSprite->getGlobalBounds();
  float bowserY = m_height / 2.f - bowserBounds.size.y / 2.f - 40.f;
  m_bowserSprite->setPosition(sf::Vector2f(m_width / 2.f - bowserBounds.size.x / 2.f, bowserY));
  // Game Over text
  auto textRect = m_gameOverText->getLocalBounds();
  m_gameOverText->setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f, textRect.position.y + textRect.size.y / 2.f));
  m_gameOverText->setPosition(sf::Vector2f(m_width / 2.f, 80.f));
  // Buttons
  float totalWidth = buttonWidth * 2 + spacing;
  float startX = m_width / 2.f - totalWidth / 2.f;
  float buttonY = m_height - 180.f;
  m_returnButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
  m_returnButton.setFillColor(sf::Color(69, 123, 157));
  m_returnButton.setPosition(sf::Vector2f(startX, buttonY));
  m_returnText->setPosition(sf::Vector2f(startX + buttonWidth / 2.f - returnWidth / 2.f, buttonY + buttonHeight / 2.f - m_returnText->getLocalBounds().size.y / 2.f));
  m_quitButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
  m_quitButton.setFillColor(sf::Color(230, 57, 70));
  m_quitButton.setPosition(sf::Vector2f(startX + buttonWidth + spacing, buttonY));
  m_quitText->setPosition(sf::Vector2f(startX + buttonWidth + spacing + buttonWidth / 2.f - quitWidth / 2.f, buttonY + buttonHeight / 2.f - m_quitText->getLocalBounds().size.y / 2.f));
}

void GameOverView::draw(sf::RenderWindow &window)
{
  // Background overlay
  sf::RectangleShape overlay(sf::Vector2f(m_width, m_height));
  overlay.setFillColor(sf::Color(255, 255, 255, 240));
  window.draw(overlay);
  if (m_gameOverText)
    window.draw(*m_gameOverText);
  if (m_bowserSprite)
    window.draw(*m_bowserSprite);
  window.draw(m_returnButton);
  if (m_returnText)
    window.draw(*m_returnText);
  window.draw(m_quitButton);
  if (m_quitText)
    window.draw(*m_quitText);
}

bool GameOverView::isReturnToMenuClicked(const sf::Vector2i &mousePos) const
{
  return m_returnButton.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

bool GameOverView::isQuitClicked(const sf::Vector2i &mousePos) const
{
  return m_quitButton.getGlobalBounds().contains(sf::Vector2f(mousePos));
}