#pragma once
#include <vector>
#include <utility>
#include "Enemy.h"

class Tower
{
public:
  Tower(std::pair<float, float> position, float range, float fireRate);
  virtual ~Tower() = default;

  virtual void update(float dt, std::vector<Enemy *> &enemies);
  std::pair<float, float> getPosition() const;
  float getRange() const;

protected:
  std::pair<float, float> position_;
  float range_;
  float fireRate_; // attacks per second
  float timeSinceLastShot_;
  virtual void attack(Enemy *enemy);
};

class FireFlowerTower : public Tower
{
public:
  FireFlowerTower(std::pair<float, float> position);

protected:
  void attack(Enemy *enemy) override;
};