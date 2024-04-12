#pragma once

#include <memory>
#include <vector>

#include "circleobstacle.h"

namespace math {

struct Path;

struct PathWayNode {
  PathWayNode(Point p) : point{p} {}
  std::vector<Path> edges;
  std::shared_ptr<CircleObstacle> circle_prt = nullptr;
  Point point;
};

struct Path {
  Path(std::shared_ptr<PathWayNode> node_ptr, double length)
      : next{node_ptr}, length{length} {}
  std::shared_ptr<PathWayNode> next;
  double length;
};

void ConnectTwoNodes(PathWayNode& node1, PathWayNode& node2, double distance) {
  node1.edges.push_back({std::make_shared<PathWayNode>(node2), distance});
  node2.edges.push_back({std::make_shared<PathWayNode>(node1), distance});
}
}  // namespace math
