#include "Projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(std::pair<float, float> position, std::pair<float, float> velocity, float damage, Enemy *target, int id)
    : position_(position), velocity_(velocity), damage_(damage), target_(target), hit_(false), id_(id) {}

void Projectile::update(float dt)
{
  if (hit_ || !target_ || !target_->isAlive())
    return;
  // Recalculate velocity to home in on the enemy
  auto [tx, ty] = target_->getPosition();
  float dx = tx - position_.first;
  float dy = ty - position_.second;
  float dist = std::sqrt(dx * dx + dy * dy);
  float speed = std::sqrt(velocity_.first * velocity_.first + velocity_.second * velocity_.second);
  if (dist > 1e-3)
  {
    velocity_.first = dx / dist * speed;
    velocity_.second = dy / dist * speed;
  }
  // Move projectile
  position_.first += velocity_.first * dt;
  position_.second += velocity_.second * dt;
  // Check for collision (simple distance check)
  dx = tx - position_.first;
  dy = ty - position_.second;
  dist = std::sqrt(dx * dx + dy * dy);
  if (dist < 0.5f)
  { // Hit threshold
    onHit();
    hit_ = true;
  }
}

bool Projectile::hasHit() const { return hit_; }
float Projectile::getDamage() const { return damage_; }
std::pair<float, float> Projectile::getPosition() const { return position_; }
Enemy *Projectile::getTarget() const { return target_; }
void Projectile::onHit()
{
  // Base class does nothing
}

FireballProjectile::FireballProjectile(std::pair<float, float> position, std::pair<float, float> velocity, Enemy *target, int id)
    : Projectile(position, velocity, 3.0f, target, id) {}

void FireballProjectile::onHit()
{
  if (target_ && target_->isAlive())
  {
    std::cout << "FireballProjectile (id=" << id_ << ") hits enemy at (" << target_->getPosition().first << ", " << target_->getPosition().second << ")!\n";
    target_->takeDamage(damage_);
  }
}

IceProjectile::IceProjectile(std::pair<float, float> position, std::pair<float, float> velocity, Enemy *target, int id)
    : Projectile(position, velocity, 2.0f, target, id) {}

void IceProjectile::onHit()
{
  if (target_ && target_->isAlive())
  {
    std::cout << "IceProjectile (id=" << id_ << ") hits enemy at (" << target_->getPosition().first << ", " << target_->getPosition().second << ")!\n";
    target_->takeDamage(damage_);
  }
}