#include "../src/models/Enemy.h"
#include <iostream>
#include <vector>

int main()
{
  std::vector<Path::Point> waypoints = {{0, 0}, {5, 0}, {5, 5}};
  Path path(waypoints);
  GoombaEnemy goomba(path);
  float dt = 1.0f;
  for (int i = 0; i < 10; ++i)
  {
    goomba.update(dt);
    auto [x, y] = goomba.getPosition();
    std::cout << "Tick " << i << ": Goomba at (" << x << ", " << y << ")\n";
  }
  return 0;
}