#pragma once

#include <vector>

#include "circleobstacle.h"

namespace math {

class MinimumDistanceCalculator {
 public:
  MinimumDistanceCalculator(Point p1, Point p2)
      : point1_{p1}, point2_{p2}, circles_(0) {}
  MinimumDistanceCalculator(Point p1, Point p2, std::vector<CircleObstacle> v)
      : point1_{p1}, point2_{p2}, circles_{v} {}

 private:
  Point point1_;
  Point point2_;
  std::vector<CircleObstacle> circles_;
  std::vector<double> ways_;

  // Заполняет вектор точек касательных для каждой окружности
  void FillTangentsCircles();

  void FillTangentsPoints(Point& point);

  double FindOptimalWay(const Point& pnt1, const Point& pnt2);
};
}  // namespace math
