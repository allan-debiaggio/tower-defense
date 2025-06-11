#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float health, float speed, const Path &path)
    : health_(health), speed_(speed), path_(path), currentWaypoint_(0)
{
  position_ = path_.getWaypoint(0);
}

void Enemy::update(float dt)
{
  float remainingDist = speed_ * dt;
  while (remainingDist > 0 && currentWaypoint_ + 1 < path_.getNumWaypoints())
  {
    auto [x, y] = position_;
    auto [tx, ty] = path_.getWaypoint(currentWaypoint_ + 1);
    float dx = tx - x;
    float dy = ty - y;
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist < 1e-3)
    {
      ++currentWaypoint_;
      continue;
    }
    if (remainingDist >= dist)
    {
      position_ = {tx, ty};
      ++currentWaypoint_;
      remainingDist -= dist;
    }
    else
    {
      position_ = {x + dx / dist * remainingDist, y + dy / dist * remainingDist};
      remainingDist = 0;
    }
  }
}

float Enemy::getHealth() const { return health_; }
std::pair<float, float> Enemy::getPosition() const { return position_; }
bool Enemy::isAlive() const { return health_ > 0; }

void Enemy::takeDamage(float amount)
{
  health_ -= amount;
  if (health_ < 0)
    health_ = 0;
}

GoombaEnemy::GoombaEnemy(const Path &path)
    : Enemy(10.0f, 0.5f, path) {}

KoopaEnemy::KoopaEnemy(const Path &path)
    : Enemy(20.0f, 0.7f, path) {}

ParagoombaEnemy::ParagoombaEnemy(const Path &path)
    : Enemy(8.0f, 1.2f, path) {}

BowserEnemy::BowserEnemy(const Path &path)
    : Enemy(30.0f, 0.5f, path) {}