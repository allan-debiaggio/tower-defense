#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float health, float speed, const Path &path)
    : health_(health), speed_(speed), path_(path), currentWaypoint_(0)
{
  position_ = path_.getWaypoint(0);
}

void Enemy::update(float dt)
{
  if (currentWaypoint_ + 1 >= path_.getNumWaypoints())
    return;
  auto [x, y] = position_;
  auto [tx, ty] = path_.getWaypoint(currentWaypoint_ + 1);
  float dx = tx - x;
  float dy = ty - y;
  float dist = std::sqrt(dx * dx + dy * dy);
  if (dist < 1e-3)
  {
    ++currentWaypoint_;
    return;
  }
  float moveDist = speed_ * dt;
  if (moveDist >= dist)
  {
    position_ = {tx, ty};
    ++currentWaypoint_;
  }
  else
  {
    position_ = {x + dx / dist * moveDist, y + dy / dist * moveDist};
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
    : Enemy(10.0f, 1.0f, path) {}