#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(std::pair<float, float> position, float range, float fireRate)
    : position_(position), range_(range), fireRate_(fireRate), timeSinceLastShot_(0.0f) {}

std::vector<Projectile *> Tower::update(float dt, std::vector<Enemy *> &enemies)
{
  timeSinceLastShot_ += dt;
  float cooldown = 1.0f / fireRate_;
  if (timeSinceLastShot_ < cooldown)
    return {};
  std::vector<Projectile *> projectiles;
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
      projectiles.push_back(attack(enemy));
      timeSinceLastShot_ = 0.0f;
      break; // Attack only one enemy per update
    }
  }
  return projectiles;
}

std::pair<float, float> Tower::getPosition() const { return position_; }
float Tower::getRange() const { return range_; }
Projectile *Tower::attack(Enemy *enemy)
{
  // Base class does nothing
  return nullptr;
}

FireFlowerTower::FireFlowerTower(std::pair<float, float> position)
    : Tower(position, 2.5f, 1.0f) // range 2.5, 1 shot/sec
{
}

Projectile *FireFlowerTower::attack(Enemy *enemy)
{
  static int projectile_id_counter = 0;
  // Calculate velocity towards enemy
  auto [ex, ey] = enemy->getPosition();
  auto [tx, ty] = position_;
  float dx = ex - tx;
  float dy = ey - ty;
  float dist = std::sqrt(dx * dx + dy * dy);
  float speed = 3.0f; // Fireball speed
  std::pair<float, float> velocity = {dx / dist * speed, dy / dist * speed};
  std::cout << "FireFlowerTower fires fireball at enemy at (" << ex << ", " << ey << ")!\n";
  return new FireballProjectile(position_, velocity, enemy, projectile_id_counter++);
}