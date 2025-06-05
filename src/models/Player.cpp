#include "Player.h"

Player::Player(int coins, int lives) : coins_(coins), lives_(lives) {}

void Player::addCoins(int amount)
{
  coins_ += amount;
}

bool Player::spendCoins(int amount)
{
  if (coins_ >= amount)
  {
    coins_ -= amount;
    return true;
  }
  return false;
}

void Player::loseLife()
{
  if (lives_ > 0)
    --lives_;
}

int Player::getCoins() const { return coins_; }
int Player::getLives() const { return lives_; }