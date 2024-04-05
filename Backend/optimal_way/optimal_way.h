#pragma once

#include <vector>

#include "pathgraph.h"

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

  double DistanceBetweenPoints(const Point& p1, const Point p2) const;

  LinearАunction MakeLinearАunction(const Point& point1,
                                    const Point& point2) const;
  // Точки касания прямой к окружснотям
  std::pair<Point, Point> CrossPoints(const LinearАunction& tangent,
                                      const CircleObstacle& circle1,
                                      const CircleObstacle& circle2) const;

  std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& crcl,
                                                const Point& point) const;

  std::vector<LinearАunction> TangentsBetweenCircles(
      const CircleObstacle& circle1, const CircleObstacle& circle2) const;

  // Пересекает ли отрезок, проведенный через две точки, окружность
  bool AreThereIntersections(const CircleObstacle& crcl, const Point& pnt1,
                             const Point& pnt2) const;

  // Заполняет вектор точек касательных для каждой окружности
  void FillTangentsCircles();

  void FillTangentsPoints(Point& point);

  double FindOptimalWay(const Point& pnt1, const Point& pnt2);
};
}  // namespace math
