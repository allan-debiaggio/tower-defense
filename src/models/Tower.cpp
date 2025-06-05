#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(std::pair<float, float> position, float range, float fireRate)
    : position_(position), range_(range), fireRate_(fireRate), timeSinceLastShot_(0.0f) {}

void Tower::update(float dt, std::vector<Enemy *> &enemies)
{
  timeSinceLastShot_ += dt;
  float cooldown = 1.0f / fireRate_;
  if (timeSinceLastShot_ < cooldown)
    return;
  for (auto *enemy : enemies)
  {
    if (!enemy->isAlive())
      continue;
    auto [ex, ey] = enemy->getPosition();
    auto [tx, ty] = position_;
    float dx = ex - tx;
    float dy = ey - ty;
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist <= range_)
    {
      attack(enemy);
      timeSinceLastShot_ = 0.0f;
      break; // Attack only one enemy per update
    }
  }
}

std::pair<float, float> Tower::getPosition() const { return position_; }
float Tower::getRange() const { return range_; }
void Tower::attack(Enemy *enemy)
{
  // Base class does nothing
}

FireFlowerTower::FireFlowerTower(std::pair<float, float> position)
    : Tower(position, 2.5f, 1.0f) // range 2.5, 1 shot/sec
{
}

void FireFlowerTower::attack(Enemy *enemy)
{
  std::cout << "FireFlowerTower attacks enemy at (" << enemy->getPosition().first << ", " << enemy->getPosition().second << ")!\n";
  enemy->takeDamage(3.0f); // Deal 3 damage
}