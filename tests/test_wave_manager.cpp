#include "../src/models/WaveManager.h"
#include <iostream>

int main()
{
  std::vector<Path::Point> waypoints = {{0, 0}, {5, 0}, {5, 5}};
  Path path(waypoints);
  int numWaves = 3;
  int enemiesPerWave = 4;
  WaveManager waveManager(numWaves, enemiesPerWave, path);
  int waveNum = 1;
  while (waveManager.hasNextWave())
  {
    std::cout << "Starting wave " << waveNum << "\n";
    waveManager.startNextWave();
    for (int tick = 0; tick < 10; ++tick)
    {
      waveManager.update(1.0f); // Advance time and spawn enemies as needed
      auto &enemies = waveManager.getActiveEnemies();
      std::cout << "Tick " << tick << ": ";
      for (size_t i = 0; i < enemies.size(); ++i)
      {
        enemies[i]->update(1.0f);
        auto [x, y] = enemies[i]->getPosition();
        std::cout << "Enemy " << i << " at (" << x << ", " << y << ") ";
      }
      std::cout << "\n";
    }
    ++waveNum;
  }
  std::cout << "All waves complete!\n";
  return 0;
}