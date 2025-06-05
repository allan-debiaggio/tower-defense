#pragma once
#include <vector>
#include <utility>

class Path
{
public:
  using Point = std::pair<float, float>;

  Path(const std::vector<Point> &waypoints);
  const Point &getWaypoint(size_t index) const;
  size_t getNumWaypoints() const;

private:
  std::vector<Point> waypoints_;
};