#pragma once
#include <vector>
#include <utility>
#include "Enemy.h"
#include "Projectile.h"

class Tower
{
public:
  Tower(std::pair<float, float> position, float range, float fireRate);
  virtual ~Tower() = default;

  virtual std::vector<Projectile *> update(float dt, std::vector<Enemy *> &enemies);
  std::pair<float, float> getPosition() const;
  float getRange() const;

  int getLevel() const;
  int getUpgradeCost() const;
  bool canUpgrade() const;
  bool upgrade(int &playerCoins); // returns true if upgraded
  int getSellValue() const;

protected:
  std::pair<float, float> position_;
  float range_;
  float fireRate_; // attacks per second
  float timeSinceLastShot_;
  virtual Projectile *attack(Enemy *enemy);

  int level_ = 0;
  int upgradeCost_ = 10;
  int totalSpent_ = 10; // Track total coins spent on this tower
};

class FireFlowerTower : public Tower
{
public:
  FireFlowerTower(std::pair<float, float> position);

protected:
  Projectile *attack(Enemy *enemy) override;
};

class IceTower : public Tower
{
public:
  IceTower(std::pair<float, float> position);

protected:
  Projectile *attack(Enemy *enemy) override;
};