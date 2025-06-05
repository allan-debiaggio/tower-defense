#include "../src/models/Player.h"
#include <iostream>

int main()
{
  Player player(10, 3);
  std::cout << "Initial coins: " << player.getCoins() << ", lives: " << player.getLives() << "\n";
  player.addCoins(5);
  std::cout << "Add 5 coins. Coins: " << player.getCoins() << "\n";
  bool spent = player.spendCoins(7);
  std::cout << "Spend 7 coins. Success: " << spent << ", Coins: " << player.getCoins() << "\n";
  spent = player.spendCoins(10);
  std::cout << "Spend 10 coins. Success: " << spent << ", Coins: " << player.getCoins() << "\n";
  player.loseLife();
  std::cout << "Lose a life. Lives: " << player.getLives() << "\n";
  player.loseLife();
  std::cout << "Lose a life. Lives: " << player.getLives() << "\n";
  player.loseLife();
  std::cout << "Lose a life. Lives: " << player.getLives() << "\n";
  player.loseLife();
  std::cout << "Lose a life. Lives: " << player.getLives() << "\n";
  return 0;
}