#include "../src/models/Enemy.h"
#include "../src/models/Tower.h"
#include "../src/models/Projectile.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
  std::vector<Path::Point> waypoints = {{0, 0}, {5, 0}, {5, 5}};
  Path path(waypoints);
  GoombaEnemy goomba(path);
  FireFlowerTower tower({2, 0}); // Place tower near the path
  std::vector<Enemy *> enemies = {&goomba};
  std::vector<Projectile *> projectiles;
  float dt = 1.0f;
  for (int i = 0; i < 15; ++i)
  {
    goomba.update(dt);
    // Tower may fire new projectiles
    auto newProjectiles = tower.update(dt, enemies);
    if (newProjectiles.empty())
    {
      // Check if enemy is out of range
      auto [ex, ey] = goomba.getPosition();
      auto [tx, ty] = tower.getPosition();
      float dx = ex - tx;
      float dy = ey - ty;
      float dist = std::sqrt(dx * dx + dy * dy);
      if (dist > tower.getRange())
      {
        std::cout << "Tick " << i << ": Enemy is out of tower's fire range!\n";
      }
    }
    for (auto *p : newProjectiles)
    {
      if (p)
        projectiles.push_back(p);
    }
    // Update all projectiles
    for (auto *proj : projectiles)
    {
      if (proj && !proj->hasHit())
        proj->update(dt);
    }
    auto [x, y] = goomba.getPosition();
    std::cout << "Tick " << i << ": Goomba at (" << x << ", " << y << ") HP: " << goomba.getHealth() << "\n";
    if (!goomba.isAlive())
    {
      std::cout << "Goomba defeated!\n";
      break;
    }
  }
  // Clean up projectiles
  for (auto *proj : projectiles)
    if (proj)
      delete proj;
  // After the main loop, check for projectiles that hit
  for (size_t i = 0; i < projectiles.size(); ++i)
  {
    if (projectiles[i] && projectiles[i]->hasHit())
    {
      auto [px, py] = projectiles[i]->getPosition();
      std::cout << "Projectile " << projectiles[i]->getId() << " hit the enemy, final position: (" << px << ", " << py << ")\n";
    }
  }
  return 0;
}