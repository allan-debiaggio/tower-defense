#pragma once
#include <utility>
#include "Enemy.h"

class Projectile
{
public:
  Projectile(std::pair<float, float> position, std::pair<float, float> velocity, float damage, Enemy *target);
  virtual ~Projectile() = default;

  virtual void update(float dt);
  bool hasHit() const;
  float getDamage() const;
  std::pair<float, float> getPosition() const;
  Enemy *getTarget() const;

protected:
  std::pair<float, float> position_;
  std::pair<float, float> velocity_;
  float damage_;
  Enemy *target_;
  bool hit_;
  virtual void onHit();
};

class FireballProjectile : public Projectile
{
public:
  FireballProjectile(std::pair<float, float> position, std::pair<float, float> velocity, Enemy *target);

protected:
  void onHit() override;
};