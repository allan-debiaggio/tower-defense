#pragma once
#include <cstddef>
#include "Path.h"

class Enemy
{
public:
  Enemy(float health, float speed, const Path &path);
  virtual ~Enemy() = default;

  virtual void update(float dt);
  float getHealth() const;
  std::pair<float, float> getPosition() const;
  bool isAlive() const;
  void takeDamage(float amount);
  bool hasReachedEnd() const { return currentWaypoint_ + 1 >= path_.getNumWaypoints(); }
  size_t getCurrentWaypoint() const { return currentWaypoint_; }
  float getSpeed() const { return speed_; }

protected:
  float health_;
  float speed_;
  std::pair<float, float> position_;
  const Path &path_;
  size_t currentWaypoint_;
};

class GoombaEnemy : public Enemy
{
public:
  GoombaEnemy(const Path &path);
  // Can override update if needed
};

class KoopaEnemy : public Enemy
{
public:
  KoopaEnemy(const Path &path);
  // Can override update if needed
};

class ParagoombaEnemy : public Enemy
{
public:
  ParagoombaEnemy(const Path &path);
};

class BowserEnemy : public Enemy
{
public:
  BowserEnemy(const Path &path);
};