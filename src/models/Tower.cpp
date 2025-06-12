#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(std::pair<float, float> position, float range, float fireRate)
    : position_(position), range_(range), fireRate_(fireRate), timeSinceLastShot_(0.0f), level_(1), upgradeCost_(10), totalSpent_(10) {}

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

IceTower::IceTower(std::pair<float, float> position)
    : Tower(position, 3.0f, 0.8f) // range 3.0, 0.8 shots/sec
{
}

Projectile *IceTower::attack(Enemy *enemy)
{
  static int projectile_id_counter = 0;
  auto [ex, ey] = enemy->getPosition();
  auto [tx, ty] = position_;
  float dx = ex - tx;
  float dy = ey - ty;
  float dist = std::sqrt(dx * dx + dy * dy);
  float speed = 2.5f; // Ice projectile speed
  std::pair<float, float> velocity = {dx / dist * speed, dy / dist * speed};
  std::cout << "IceTower fires ice projectile at enemy at (" << ex << ", " << ey << ")!\n";
  return new IceProjectile(position_, velocity, enemy, projectile_id_counter++);
}

int Tower::getLevel() const { return level_; }
int Tower::getUpgradeCost() const { return upgradeCost_; }
bool Tower::canUpgrade() const { return level_ < 3; }
bool Tower::upgrade(int &playerCoins)
{
  if (!canUpgrade() || playerCoins < upgradeCost_)
    return false;
  playerCoins -= upgradeCost_;
  ++level_;
  range_ *= 1.2f;
  fireRate_ *= 1.2f;
  totalSpent_ += upgradeCost_; // Track upgrade spending
  upgradeCost_ = static_cast<int>(upgradeCost_ * 1.5f);
  return true;
}
int Tower::getSellValue() const
{
  return static_cast<int>(totalSpent_ * 0.75f);
}