#pragma once

class Player
{
public:
  Player(int coins = 0, int lives = 3);
  void addCoins(int amount);
  bool spendCoins(int amount);
  void loseLife();
  int getCoins() const;
  int getLives() const;

private:
  int coins_;
  int lives_;
};