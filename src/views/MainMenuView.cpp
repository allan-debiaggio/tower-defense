#include "MainMenuView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

MainMenuView::MainMenuView(unsigned int width, unsigned int height)
    : m_width(width), m_height(height),
      m_font(),
      m_marioTexture(), m_peachTexture(), m_bowserTexture(), m_goombaTexture(),
      m_newGameButton(), m_quitButton(),
      m_showNameInput(false),
      m_nameInputBox(),
      m_playerName(),
      m_mode(MenuMode::Main),
      m_levelNames(),
      m_levelButtons()
{
  // Load textures
  m_marioTexture.loadFromFile("presentation/assets/mario.png");
  m_peachTexture.loadFromFile("presentation/assets/peach.png");
  m_bowserTexture.loadFromFile("presentation/assets/bowser1.png");
  m_goombaTexture.loadFromFile("presentation/assets/goomba.png");

  // Set textures to sprites (emplace after loading)
  m_marioSprite.emplace(m_marioTexture);
  m_peachSprite.emplace(m_peachTexture);
  m_bowserSprite.emplace(m_bowserTexture);
  m_goombaSprite.emplace(m_goombaTexture);

  // Load font
  if (!m_font.openFromFile("presentation/assets/PressStart2P.ttf"))
  {
    std::cerr << "[ERROR] Failed to load font PressStart2P.ttf!" << std::endl;
  }

  // Set font to texts (emplace after loading)
  m_title.emplace(m_font, "Super Mario Tower Defense", 38);
  m_title->setFillColor(sf::Color(230, 57, 70));
  m_title->setStyle(sf::Text::Bold);
  m_title->setPosition(sf::Vector2f(width / 2 - 340, 60));

  m_newGameText.emplace(m_font, "New Game", 24);
  m_newGameText->setFillColor(sf::Color(69, 123, 157));
  m_newGameText->setPosition(sf::Vector2f(width / 2 - 110, height / 2 - 20));

  m_quitText.emplace(m_font, "Quit", 24);
  m_quitText->setFillColor(sf::Color(69, 123, 157));
  m_quitText->setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 80));

  m_nameInputPrompt.emplace(m_font, "Enter your name:", 20);
  m_nameInputPrompt->setPosition(sf::Vector2f(width / 2 - 220, height / 2 - 40));

  m_nameInputText.emplace(m_font, "", 24);
  m_nameInputText->setFillColor(sf::Color(230, 57, 70));
  m_nameInputText->setPosition(sf::Vector2f(width / 2 - 220, height / 2 + 10));

  // Position sprites
  m_marioSprite->setPosition(sf::Vector2f(60, height - 340));
  m_goombaSprite->setPosition(sf::Vector2f(220, height - 200));
  m_peachSprite->setPosition(sf::Vector2f(width - 320, height - 340));
  m_bowserSprite->setPosition(sf::Vector2f(width - 180, height - 200));
  // New Game button
  m_newGameButton.setSize(sf::Vector2f(340, 70));
  m_newGameButton.setPosition(sf::Vector2f(width / 2 - 180, height / 2 - 40));
  m_newGameButton.setFillColor(sf::Color(255, 251, 230));
  m_newGameButton.setOutlineColor(sf::Color(255, 179, 71));
  m_newGameButton.setOutlineThickness(6);
  // Quit button
  m_quitButton.setSize(sf::Vector2f(340, 70));
  m_quitButton.setPosition(sf::Vector2f(width / 2 - 180, height / 2 + 60));
  m_quitButton.setFillColor(sf::Color(255, 251, 230));
  m_quitButton.setOutlineColor(sf::Color(255, 179, 71));
  m_quitButton.setOutlineThickness(6);
  // Name input popup
  m_nameInputBox.setSize(sf::Vector2f(500, 120));
  m_nameInputBox.setPosition(sf::Vector2f(width / 2 - 250, height / 2 - 60));
  m_nameInputBox.setFillColor(sf::Color(255, 251, 230));
  m_nameInputBox.setOutlineColor(sf::Color(230, 57, 70));
  m_nameInputBox.setOutlineThickness(6);
}

void MainMenuView::draw(sf::RenderWindow &window)
{
  if (m_mode == MenuMode::LevelSelect)
  {
    drawLevelSelection(window);
    return;
  }
  // Draw Mario background, scaled proportionally
  float scale = std::min((float)m_width / m_marioSprite->getTexture().getSize().x, (float)m_height / m_marioSprite->getTexture().getSize().y);
  m_marioSprite->setScale(sf::Vector2f(scale, scale));
  m_marioSprite->setPosition(sf::Vector2f((m_width - m_marioSprite->getGlobalBounds().size.x) / 2, 0));
  window.draw(*m_marioSprite);

  // Draw semi-transparent overlay behind menu
  sf::RectangleShape overlay(sf::Vector2f(m_width, m_height));
  overlay.setFillColor(sf::Color(0, 0, 0, 120));
  window.draw(overlay);

  // Draw title
  if (m_title)
  {
    m_title->setCharacterSize(28);
    sf::FloatRect titleRect = m_title->getLocalBounds();
    m_title->setOrigin(sf::Vector2f(titleRect.position.x + titleRect.size.x / 2, titleRect.position.y + titleRect.size.y / 2));
    m_title->setPosition(sf::Vector2f(m_width / 2, 40));
    window.draw(*m_title);
  }

  // Draw menu buttons and text
  window.draw(m_newGameButton);
  window.draw(m_quitButton);
  if (m_newGameText)
  {
    m_newGameText->setFillColor(sf::Color::Black);
    m_newGameText->setCharacterSize(32);
    // Center text in button
    sf::FloatRect textRect = m_newGameText->getLocalBounds();
    m_newGameText->setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2, textRect.position.y + textRect.size.y / 2));
    m_newGameText->setPosition(sf::Vector2f(m_newGameButton.getPosition().x + m_newGameButton.getSize().x / 2, m_newGameButton.getPosition().y + m_newGameButton.getSize().y / 2));
    window.draw(*m_newGameText);
  }
  if (m_quitText)
  {
    m_quitText->setFillColor(sf::Color::Black);
    m_quitText->setCharacterSize(32);
    sf::FloatRect textRect = m_quitText->getLocalBounds();
    m_quitText->setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2, textRect.position.y + textRect.size.y / 2));
    m_quitText->setPosition(sf::Vector2f(m_quitButton.getPosition().x + m_quitButton.getSize().x / 2, m_quitButton.getPosition().y + m_quitButton.getSize().y / 2));
    window.draw(*m_quitText);
  }

  // Draw name entry popup if active
  if (m_showNameInput)
  {
    sf::RectangleShape popup(sf::Vector2f(400, 160));
    popup.setFillColor(sf::Color(255, 255, 255, 240));
    popup.setOutlineColor(sf::Color(69, 123, 157));
    popup.setOutlineThickness(4);
    popup.setPosition(sf::Vector2f(m_width / 2 - 200, m_height / 2 - 80));
    window.draw(popup);
    if (m_nameInputPrompt)
    {
      m_nameInputPrompt->setFillColor(sf::Color::Black);
      m_nameInputPrompt->setCharacterSize(24);
      m_nameInputPrompt->setPosition(sf::Vector2f(m_width / 2 - 180, m_height / 2 - 60));
      window.draw(*m_nameInputPrompt);
    }
    if (m_nameInputText)
    {
      m_nameInputText->setFillColor(sf::Color(69, 123, 157));
      m_nameInputText->setCharacterSize(32);
      m_nameInputText->setPosition(sf::Vector2f(m_width / 2 - 180, m_height / 2 - 10));
      m_nameInputText->setString(m_playerName);
      window.draw(*m_nameInputText);
    }
  }
}

void MainMenuView::drawLevelSelection(sf::RenderWindow &window)
{
  // Draw a simple level selection UI
  float buttonWidth = 340;
  float buttonHeight = 70;
  float spacing = 30;
  float startY = m_height / 2 - ((buttonHeight + spacing) * m_levelButtons.size()) / 2;
  for (size_t i = 0; i < m_levelButtons.size(); ++i)
  {
    m_levelButtons[i].setPosition(sf::Vector2f(m_width / 2 - buttonWidth / 2, startY + i * (buttonHeight + spacing)));
    window.draw(m_levelButtons[i]);
    sf::Text label(m_font, m_levelNames[i], 24);
    label.setFillColor(sf::Color::Black);
    label.setPosition(sf::Vector2f(m_width / 2 - buttonWidth / 2 + 30, startY + i * (buttonHeight + spacing) + 18));
    window.draw(label);
  }
}

void MainMenuView::setLevelNames(const std::vector<std::string> &names)
{
  m_levelNames = names;
  m_levelButtons.clear();
  for (size_t i = 0; i < m_levelNames.size(); ++i)
  {
    sf::RectangleShape btn(sf::Vector2f(340, 70));
    btn.setFillColor(sf::Color(255, 251, 230));
    btn.setOutlineColor(sf::Color(255, 179, 71));
    btn.setOutlineThickness(6);
    m_levelButtons.push_back(btn);
  }
}

void MainMenuView::setMode(MenuMode mode)
{
  m_mode = mode;
}

MainMenuView::MenuMode MainMenuView::getMode() const
{
  return m_mode;
}

int MainMenuView::getLevelClicked(const sf::Vector2i &mousePos) const
{
  if (m_mode != MenuMode::LevelSelect)
    return -1;
  for (size_t i = 0; i < m_levelButtons.size(); ++i)
  {
    if (m_levelButtons[i].getGlobalBounds().contains(sf::Vector2f(mousePos)))
      return static_cast<int>(i);
  }
  return -1;
}

bool MainMenuView::isNewGameClicked(const sf::Vector2i &mousePos) const
{
  return m_newGameButton.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

bool MainMenuView::isQuitClicked(const sf::Vector2i &mousePos) const
{
  return m_quitButton.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

void MainMenuView::showNameInput(bool show)
{
  m_showNameInput = show;
  if (show)
    m_playerName.clear();
}

bool MainMenuView::isNameInputActive() const
{
  return m_showNameInput;
}

void MainMenuView::handleTextInput(const sf::Event &event)
{
  if (!m_showNameInput)
    return;
  if (const auto *textEvent = event.getIf<sf::Event::TextEntered>())
  {
    auto unicode = textEvent->unicode;
    if (unicode == 8)
    { // Backspace
      if (!m_playerName.empty())
        m_playerName.pop_back();
    }
    else if (unicode >= 32 && unicode < 128 && m_playerName.size() < 16)
    {
      m_playerName += static_cast<char>(unicode);
    }
  }
}

std::string MainMenuView::getPlayerName() const
{
  return m_playerName;
}