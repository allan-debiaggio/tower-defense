#include "TowerPlacementController.h"
#include "../models/Tower.h"
#include <iostream>

TowerPlacementController::TowerPlacementController(LevelManager *level, Player *player, unsigned int tileSize)
    : m_level(level), m_player(player), m_tileSize(tileSize)
{
  if (m_crownTexture.loadFromFile("assets/ui_crown.png"))
    m_crownTextureLoaded = true;
  if (m_moneyBagTexture.loadFromFile("assets/ui_money_bag.png"))
    m_moneyBagTextureLoaded = true;
}

void TowerPlacementController::handleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
  if (event.is<sf::Event::MouseButtonPressed>())
  {
    if (const auto *mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
      if (mouseEvent->button == sf::Mouse::Button::Left)
      {
        int mouseX = mouseEvent->position.x;
        int mouseY = mouseEvent->position.y;
        sf::Vector2i cell = getCellFromMouse(window, mouseX, mouseY);
        if (!m_showPopup && !m_showUpgradePopup)
        {
          // If clicking on a tower, show upgrade/sell popup
          Tower *tower = m_level->getTower(cell.x, cell.y);
          if (tower)
          {
            showUpgradePopupAtCell(cell);
            return;
          }
          // Otherwise, show placement popup
          showPopupAtCell(cell);
        }
        else if (m_showPopup)
        {
          // Check if click is inside popup menu
          sf::Vector2f popupPos(m_popupCell.x * m_tileSize, m_popupCell.y * m_tileSize);
          sf::FloatRect popupRect(popupPos, sf::Vector2f(m_tileSize * 2, m_tileSize));
          if (popupRect.contains(sf::Vector2f(mouseX, mouseY)))
          {
            // Determine which tower type was clicked
            float relX = mouseX - popupPos.x;
            if (relX < m_tileSize)
            {
              m_selectedType = TowerType::FireFlower;
            }
            else
            {
              m_selectedType = TowerType::IceTower;
            }
            tryPlaceTower(m_popupCell, m_selectedType);
            hidePopup();
          }
          else
          {
            // Clicked outside popup, hide it
            hidePopup();
          }
        }
        else if (m_showUpgradePopup)
        {
          // Handle upgrade/sell popup click
          sf::Vector2f popupPos(m_upgradePopupCell.x * m_tileSize, m_upgradePopupCell.y * m_tileSize);
          sf::FloatRect popupRect(popupPos, sf::Vector2f(m_tileSize * 2, m_tileSize));
          if (popupRect.contains(sf::Vector2f(mouseX, mouseY)))
          {
            float relX = mouseX - popupPos.x;
            if (relX < m_tileSize)
            {
              tryUpgradeTower(m_upgradePopupCell);
            }
            else
            {
              trySellTower(m_upgradePopupCell);
            }
            hideUpgradePopup();
          }
          else
          {
            hideUpgradePopup();
          }
        }
      }
    }
  }
  else if (event.is<sf::Event::MouseMoved>() && m_showPopup)
  {
    if (const auto *moveEvent = event.getIf<sf::Event::MouseMoved>())
    {
      int mouseX = moveEvent->position.x;
      int mouseY = moveEvent->position.y;
      sf::Vector2i cell = getCellFromMouse(window, mouseX, mouseY);
      m_lastPlacementValid = m_level->isBuildable(cell.x, cell.y);
    }
  }
}

void TowerPlacementController::draw(sf::RenderWindow &window)
{
  if (m_showPopup)
  {
    drawPopupMenu(window);
  }
  if (m_showUpgradePopup)
  {
    drawUpgradePopupMenu(window);
  }
  // Draw placement feedback if hovering
  if (m_showPopup)
  {
    drawPlacementFeedback(window, m_popupCell, m_lastPlacementValid);
  }
  drawMessage(window);
}

bool TowerPlacementController::towerPlaced() const
{
  return m_towerPlaced;
}
void TowerPlacementController::resetTowerPlaced()
{
  m_towerPlaced = false;
}

sf::Vector2i TowerPlacementController::getCellFromMouse(const sf::RenderWindow &window, int mouseX, int mouseY) const
{
  return sf::Vector2i(mouseX / static_cast<int>(m_tileSize), mouseY / static_cast<int>(m_tileSize));
}
void TowerPlacementController::showPopupAtCell(const sf::Vector2i &cell)
{
  m_showPopup = true;
  m_popupCell = cell;
  m_lastPlacementValid = m_level->isBuildable(cell.x, cell.y);
}
void TowerPlacementController::hidePopup()
{
  m_showPopup = false;
  m_selectedType = TowerType::None;
}
void TowerPlacementController::tryPlaceTower(const sf::Vector2i &cell, TowerType type)
{
  if (!m_level->isBuildable(cell.x, cell.y))
  {
    m_lastPlacementValid = false;
    return;
  }
  int cost = 10; // Placeholder cost
  if (m_player->getCoins() < cost)
  {
    m_lastPlacementValid = false;
    return;
  }
  std::unique_ptr<Tower> tower;
  if (type == TowerType::FireFlower)
  {
    tower = std::make_unique<FireFlowerTower>(std::make_pair((float)cell.x, (float)cell.y));
  }
  else if (type == TowerType::IceTower)
  {
    tower = std::make_unique<IceTower>(std::make_pair((float)cell.x, (float)cell.y));
  }
  else
  {
    return;
  }
  if (m_level->placeTower(cell.x, cell.y, std::move(tower)))
  {
    m_player->spendCoins(cost);
    m_towerPlaced = true;
    m_lastPlacementValid = true;
  }
  else
  {
    m_lastPlacementValid = false;
  }
}
void TowerPlacementController::drawPopupMenu(sf::RenderWindow &window)
{
  sf::Vector2f popupPos(m_popupCell.x * m_tileSize, m_popupCell.y * m_tileSize);
  sf::RectangleShape popupBg(sf::Vector2f(m_tileSize * 2, m_tileSize));
  popupBg.setPosition(popupPos);
  popupBg.setFillColor(sf::Color(240, 240, 240, 230));
  popupBg.setOutlineColor(sf::Color::Black);
  popupBg.setOutlineThickness(2);
  window.draw(popupBg);
  // FireFlower (left)
  sf::CircleShape fireFlower(m_tileSize / 3);
  fireFlower.setFillColor(sf::Color(255, 80, 40));
  fireFlower.setPosition(sf::Vector2f(popupPos.x + m_tileSize / 6, popupPos.y + m_tileSize / 6));
  window.draw(fireFlower);
  // IceTower (right)
  sf::CircleShape iceTower(m_tileSize / 3);
  iceTower.setFillColor(sf::Color(80, 180, 255));
  iceTower.setPosition(sf::Vector2f(popupPos.x + m_tileSize + m_tileSize / 6, popupPos.y + m_tileSize / 6));
  window.draw(iceTower);
  // Tower names (placeholder)
  sf::Font font;
  if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial Bold.ttf"))
  {
    sf::Text fireText(font, "Fire", 14);
    fireText.setFillColor(sf::Color::Black);
    fireText.setPosition(sf::Vector2f(popupPos.x + 4, popupPos.y + m_tileSize / 2));
    window.draw(fireText);
    sf::Text iceText(font, "Ice", 14);
    iceText.setFillColor(sf::Color::Black);
    iceText.setPosition(sf::Vector2f(popupPos.x + m_tileSize + 4, popupPos.y + m_tileSize / 2));
    window.draw(iceText);
  }
}
void TowerPlacementController::drawPlacementFeedback(sf::RenderWindow &window, const sf::Vector2i &cell, bool valid)
{
  sf::RectangleShape highlight(sf::Vector2f(m_tileSize, m_tileSize));
  highlight.setPosition(sf::Vector2f(cell.x * m_tileSize, cell.y * m_tileSize));
  highlight.setFillColor(sf::Color(0, 0, 0, 0));
  highlight.setOutlineThickness(4);
  highlight.setOutlineColor(valid ? sf::Color(0, 200, 0, 180) : sf::Color(200, 0, 0, 180));
  window.draw(highlight);
}

void TowerPlacementController::showUpgradePopupAtCell(const sf::Vector2i &cell)
{
  m_showUpgradePopup = true;
  m_upgradePopupCell = cell;
}
void TowerPlacementController::hideUpgradePopup()
{
  m_showUpgradePopup = false;
}

void TowerPlacementController::tryUpgradeTower(const sf::Vector2i &cell)
{
  Tower *tower = m_level->getTower(cell.x, cell.y);
  if (!tower)
    return;
  if (!tower->canUpgrade())
  {
    m_message = "Maximum level reached";
    m_messageTimer = 2.5f;
    return;
  }
  int cost = tower->getUpgradeCost();
  if (m_player->getCoins() < cost)
  {
    m_message = "Not enough coins";
    m_messageTimer = 2.5f;
    return;
  }
  int coins = m_player->getCoins();
  if (tower->upgrade(coins))
  {
    m_player->spendCoins(cost); // sync coins
    m_message = "Tower upgraded!";
    m_messageTimer = 1.5f;
  }
  else
  {
    m_message = "Upgrade failed";
    m_messageTimer = 2.0f;
  }
}
void TowerPlacementController::trySellTower(const sf::Vector2i &cell)
{
  Tower *tower = m_level->getTower(cell.x, cell.y);
  if (!tower)
    return;
  int value = tower->getSellValue();
  m_player->addCoins(value);
  m_level->removeTower(cell.x, cell.y);
  m_message = "Tower sold!";
  m_messageTimer = 1.5f;
}

void TowerPlacementController::drawUpgradePopupMenu(sf::RenderWindow &window)
{
  sf::Vector2f popupPos(m_upgradePopupCell.x * m_tileSize, m_upgradePopupCell.y * m_tileSize);
  sf::RectangleShape popupBg(sf::Vector2f(m_tileSize * 2, m_tileSize));
  popupBg.setPosition(popupPos);
  popupBg.setFillColor(sf::Color(255, 255, 240, 240));
  popupBg.setOutlineColor(sf::Color::Black);
  popupBg.setOutlineThickness(2);
  window.draw(popupBg);
  // Crown icon (upgrade, left)
  if (m_crownTextureLoaded)
  {
    sf::Sprite crown(m_crownTexture);
    crown.setScale(sf::Vector2f(m_tileSize * 0.85f / m_crownTexture.getSize().x, m_tileSize * 0.85f / m_crownTexture.getSize().y));
    crown.setPosition(sf::Vector2f(popupPos.x + m_tileSize * 0.075f, popupPos.y + m_tileSize * 0.075f));
    window.draw(crown);
  }
  // Money bag icon (sell, right)
  if (m_moneyBagTextureLoaded)
  {
    sf::Sprite bag(m_moneyBagTexture);
    bag.setScale(sf::Vector2f(m_tileSize * 0.85f / m_moneyBagTexture.getSize().x, m_tileSize * 0.85f / m_moneyBagTexture.getSize().y));
    bag.setPosition(sf::Vector2f(popupPos.x + m_tileSize + m_tileSize * 0.075f, popupPos.y + m_tileSize * 0.075f));
    window.draw(bag);
  }
  // No text labels, just icons
}

void TowerPlacementController::drawMessage(sf::RenderWindow &window)
{
  if (m_messageTimer > 0.0f && !m_message.empty())
  {
    sf::Font font;
    if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial Bold.ttf"))
    {
      sf::Text msg(font, m_message, 28);
      msg.setFillColor(sf::Color(255, 220, 40));
      msg.setOutlineColor(sf::Color::Black);
      msg.setOutlineThickness(3);
      msg.setStyle(sf::Text::Bold);
      auto bounds = msg.getLocalBounds();
      float x = (window.getSize().x - bounds.size.x) / 2.0f;
      float y = window.getSize().y - 60.0f;
      msg.setPosition(sf::Vector2f(x, y));
      window.draw(msg);
    }
    // Decrement timer (should be called from update, but for now, do it here)
    m_messageTimer -= 1.0f / 60.0f; // Approximate for 60 FPS
    if (m_messageTimer <= 0.0f)
    {
      m_message.clear();
      m_messageTimer = 0.0f;
    }
  }
}