#pragma once

#include <memory>
#include <vector>

#include "circleobstacle.h"
namespace math {

struct PathWayNode {
  PathWayNode(Point p) : point{p} {}
  std::vector<std::shared_ptr<PathWayNode>> edges;
  std::unique_ptr<CircleObstacle> circle_prt = nullptr;
  Point point;
};

class PathGraph {
 public:
  PathGraph(std::vector<CircleObstacle> obstacles, Point point1, Point point2);

 private:
  std::vector<PathWayNode> graph_;

  double FindTheShortestWay();
};

}  // namespace math
