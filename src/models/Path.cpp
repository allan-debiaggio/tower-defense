#include "Path.h"

Path::Path(const std::vector<Point> &waypoints) : waypoints_(waypoints) {}

const Path::Point &Path::getWaypoint(size_t index) const
{
  return waypoints_.at(index);
}

size_t Path::getNumWaypoints() const
{
  return waypoints_.size();
}