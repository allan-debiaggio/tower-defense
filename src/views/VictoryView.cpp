#include "VictoryView.h"
#include <iostream>

VictoryView::VictoryView(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
  if (!m_font.openFromFile("presentation/assets/PressStart2P.ttf"))
  {
    std::cerr << "[VictoryView] Failed to load font!" << std::endl;
  }
  if (!m_bowserTexture.loadFromFile("presentation/assets/bowser2.png"))
  {
    std::cerr << "[VictoryView] Failed to load bowser2.png!" << std::endl;
  }
  m_bowserSprite.emplace(m_bowserTexture);
  m_victoryText.emplace(m_font, "Victory!", 48);
  m_victoryText->setFillColor(sf::Color(69, 123, 157));
  m_victoryText->setStyle(sf::Text::Bold);
  m_returnText.emplace(m_font, "Return to Menu", 28);
  m_returnText->setFillColor(sf::Color::Black);
  m_returnButton.setSize(sf::Vector2f(340, 70));
  m_returnButton.setFillColor(sf::Color(255, 251, 230));
  m_returnButton.setOutlineColor(sf::Color(255, 179, 71));
  m_returnButton.setOutlineThickness(6);
  layout();
}

void VictoryView::setMode(Mode mode)
{
  m_mode = mode;
  layout();
}

void VictoryView::layout()
{
  // Calculate button width based on text
  float padding = 60.f;
  float returnWidth = m_returnText->getLocalBounds().size.x;
  float buttonWidth = returnWidth + padding;
  float buttonHeight = 70.f;
  // Center Bowser image higher
  float bowserScale = std::min((float)m_width / 2.0f / m_bowserTexture.getSize().x, (float)m_height / 2.5f / m_bowserTexture.getSize().y);
  m_bowserSprite->setScale(sf::Vector2f(bowserScale, bowserScale));
  auto bowserBounds = m_bowserSprite->getGlobalBounds();
  float bowserY = m_height / 2.f - bowserBounds.size.y / 2.f - 40;
  m_bowserSprite->setPosition(sf::Vector2f(m_width / 2.f - bowserBounds.size.x / 2.f, bowserY));
  // Center victory text at top
  auto textRect = m_victoryText->getLocalBounds();
  m_victoryText->setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f, textRect.position.y + textRect.size.y / 2.f));
  m_victoryText->setPosition(sf::Vector2f(m_width / 2.f, 100));
  // Button (only for FinalVictory)
  float buttonX = m_width / 2.f - buttonWidth / 2.f;
  float returnY = m_height - 180;
  m_returnButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
  m_returnButton.setPosition(sf::Vector2f(buttonX, returnY));
  m_returnText->setPosition(sf::Vector2f(m_width / 2.f - returnWidth / 2.f, returnY + 18));
}

void VictoryView::draw(sf::RenderWindow &window)
{
  // Background overlay
  sf::RectangleShape overlay(sf::Vector2f(m_width, m_height));
  overlay.setFillColor(sf::Color(255, 255, 255, 240));
  window.draw(overlay);
  if (m_victoryText)
    window.draw(*m_victoryText);
  if (m_bowserSprite)
    window.draw(*m_bowserSprite);
  if (m_mode == Mode::FinalVictory)
  {
    window.draw(m_returnButton);
    if (m_returnText)
      window.draw(*m_returnText);
  }
}

bool VictoryView::isReturnToMenuClicked(const sf::Vector2i &mousePos) const
{
  if (m_mode != Mode::FinalVictory)
    return false;
  return m_returnButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}