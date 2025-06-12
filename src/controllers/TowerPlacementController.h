#pragma once
#include <SFML/Graphics.hpp>
#include "../models/LevelManager.h"
#include "../models/Player.h"
#include <memory>
#include <optional>

class TowerPlacementController
{
public:
  TowerPlacementController(LevelManager *level, Player *player, unsigned int tileSize);
  // Call this from the main event loop
  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
  // Call this from the view's draw/render method
  void draw(sf::RenderWindow &window);
  // Returns true if a tower was placed
  bool towerPlaced() const;
  void resetTowerPlaced();

private:
  LevelManager *m_level;
  Player *m_player;
  unsigned int m_tileSize;
  // Popup menu state
  bool m_showPopup = false;
  sf::Vector2i m_popupCell; // grid cell where popup is shown
  // Tower selection
  enum class TowerType
  {
    None,
    FireFlower,
    IceTower
  };
  TowerType m_selectedType = TowerType::None;
  // Placement feedback
  bool m_lastPlacementValid = false;
  bool m_towerPlaced = false;
  // Helper
  sf::Vector2i getCellFromMouse(const sf::RenderWindow &window, int mouseX, int mouseY) const;
  void showPopupAtCell(const sf::Vector2i &cell);
  void hidePopup();
  void tryPlaceTower(const sf::Vector2i &cell, TowerType type);
  void drawPopupMenu(sf::RenderWindow &window);
  void drawPlacementFeedback(sf::RenderWindow &window, const sf::Vector2i &cell, bool valid);
};