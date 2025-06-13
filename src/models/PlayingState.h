#pragma once
#include "GameState.h"
#include "../views/GameView.h"
#include "../views/HUDView.h"
#include "../controllers/TowerPlacementController.h"
#include <list>
#include <memory>

class PlayingState : public GameState
{
public:
  PlayingState();
  PlayingState(unsigned int windowWidth, unsigned int windowHeight);
  void enter(GameManager &manager) override;
  void update(GameManager &manager, float dt) override;
  void handleInput(GameManager &manager) override;
  void exit(GameManager &manager) override;
  void handleEvent(const sf::Event &event, sf::RenderWindow &window, GameManager &manager) override;
  void draw(sf::RenderWindow &window) override;

private:
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;
  std::unique_ptr<GameView> m_gameView;
  std::unique_ptr<HUDView> m_hudView;
  std::unique_ptr<TowerPlacementController> m_placementController;
  std::list<std::unique_ptr<Projectile>> m_activeProjectiles;
  Player *m_player = nullptr;
  LevelManager *m_level = nullptr;
};