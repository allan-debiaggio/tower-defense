#include "../src/models/Enemy.h"
#include "../src/models/Tower.h"
#include <iostream>
#include <vector>

int main()
{
  std::vector<Path::Point> waypoints = {{0, 0}, {5, 0}, {5, 5}};
  Path path(waypoints);
  GoombaEnemy goomba(path);
  FireFlowerTower tower({2, 0}); // Place tower near the path
  std::vector<Enemy *> enemies = {&goomba};
  float dt = 1.0f;
  for (int i = 0; i < 10; ++i)
  {
    goomba.update(dt);
    tower.update(dt, enemies);
    auto [x, y] = goomba.getPosition();
    std::cout << "Tick " << i << ": Goomba at (" << x << ", " << y << ") HP: " << goomba.getHealth() << "\n";
    if (!goomba.isAlive())
    {
      std::cout << "Goomba defeated!\n";
      break;
    }
  }
  return 0;
}