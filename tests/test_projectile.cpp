#include "../src/models/Enemy.h"
#include "../src/models/Projectile.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
  std::vector<Path::Point> waypoints = {{0, 0}, {5, 0}, {5, 5}};
  Path path(waypoints);
  GoombaEnemy goomba(path);
  // Fireball starts at (0,0), target is goomba, velocity points right
  FireballProjectile fireball({0, 0}, {2, 0}, &goomba);
  float dt = 1.0f;
  for (int i = 0; i < 10; ++i)
  {
    goomba.update(dt);
    fireball.update(dt);
    auto [x, y] = fireball.getPosition();
    std::cout << "Tick " << i << ": Fireball at (" << x << ", " << y << ")\n";
    if (fireball.hasHit())
    {
      std::cout << "Goomba HP: " << goomba.getHealth() << "\n";
      break;
    }
  }
  return 0;
}