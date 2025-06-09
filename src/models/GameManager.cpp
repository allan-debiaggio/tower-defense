#include "GameManager.h"

GameManager::GameManager() : currentLevelIndex_(0) {}

void GameManager::addLevel(std::unique_ptr<LevelManager> level)
{
  levels_.push_back(std::move(level));
}

LevelManager *GameManager::getCurrentLevel()
{
  if (levels_.empty() || currentLevelIndex_ < 0 || currentLevelIndex_ >= levels_.size())
    return nullptr;
  return levels_[currentLevelIndex_].get();
}

bool GameManager::nextLevel()
{
  if (hasNextLevel())
  {
    ++currentLevelIndex_;
    return true;
  }
  return false;
}

bool GameManager::hasNextLevel() const
{
  return currentLevelIndex_ + 1 < levels_.size();
}

void GameManager::resetCurrentLevel()
{
  if (getCurrentLevel())
    getCurrentLevel()->reset();
}

int GameManager::getCurrentLevelIndex() const
{
  return currentLevelIndex_;
}

int GameManager::getTotalLevels() const
{
  return levels_.size();
}

void GameManager::setState(std::unique_ptr<GameState> newState)
{
  if (currentState_)
    currentState_->exit(*this);
  currentState_ = std::move(newState);
  if (currentState_)
    currentState_->enter(*this);
}

void GameManager::update(float dt)
{
  if (currentState_)
    currentState_->update(*this, dt);
}

void GameManager::handleInput()
{
  if (currentState_)
    currentState_->handleInput(*this);
}

void GameManager::setPlayerName(const std::string &name)
{
  playerName_ = name;
}

const std::string &GameManager::getPlayerName() const
{
  return playerName_;
}

Player &GameManager::getPlayer()
{
  return player_;
}

void GameManager::resetPlayer()
{
  player_ = Player();
  playerName_.clear();
}