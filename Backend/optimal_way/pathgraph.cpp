#include "pathgraph.h"

namespace math {

PathGraph::PathGraph(std::vector<CircleObstacle> obstacles, Point point1,
                     Point point2) {
  for (auto& obstacle : obstacles) {
    for (auto& point : obstacle.GetTangentPoints()) {
      if (point.another_tangent_point) {
        PathWayNode new_node{point};
        new_node.circle_prt = std::make_unique<CircleObstacle>(obstacle);
        for (auto& prev : graph_) {
          if (prev.circle_prt && ((*prev.circle_prt) == obstacle)) {
            prev.edges.push_back(std::make_shared<PathWayNode>(new_node));
            new_node.edges.push_back(std::make_shared<PathWayNode>(prev));
          } else if (prev.circle_prt &&
                     (new_node.point == (*prev.point.another_tangent_point))) {
            prev.edges.push_back(std::make_shared<PathWayNode>(new_node));
            new_node.edges.push_back(std::make_shared<PathWayNode>(prev));
          }
        }
        graph_.push_back(new_node);
      }
    }
  }
}
}  // namespace math
