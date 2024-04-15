#pragma once

#include <vector>

#include "path_graph.h"

namespace math {

class MinimumDistanceCalculator {
 public:
  MinimumDistanceCalculator(Point p1, Point p2, std::vector<CircleObstacle> v)
      : point1_{p1}, point2_{p2}, circles_{v} {
    FindOptimalWay();
  }

  std::vector<std::size_t> GetOptimalWay() { return optimal_way_; }

 private:
  Point point1_;

  Point point2_;

  std::vector<CircleObstacle> circles_;

  PathWayGraph graph_;

  std::vector<std::size_t> optimal_way_;

  bool TangentGoesTroughOtherCircle(const LinearFunction& tangent,
                                    int circle1_index, int circle2_index);

  void AddTangent(const LinearFunction& tangent, CircleObstacle& circle1,
                  CircleObstacle& circle2);

  // Заполняет вектор точек касательных для каждой окружности
  void FillTangentsCircles();

  void FillTangentsPoints(Point& point);

  void FillPathNodesOnCircles();

  void FillPathNodesOnPoint(const Point& point);

  void FindOptimalWay();
};

}  // namespace math
