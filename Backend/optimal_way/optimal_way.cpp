#include "optimal_way.h"

#include "helpers_functions.h"
#include "pathgraph.h"

namespace math {

bool MinimumDistanceCalculator::TangentGoesTroughOtherCircle(
    const LinearАunction& tangent, int circle1_index, int circle2_index) {
  std::pair<Point, Point> tangent_points =
      CrossPoints(tangent, circles_[circle1_index], circles_[circle2_index]);
  for (int l = 0; l < circles_.size(); ++l)
    if (l != circle1_index && l != circle2_index)
      if (AreThereIntersections(circles_[l], tangent_points.first,
                                tangent_points.second))
        return true;
  return false;
}

void MinimumDistanceCalculator::AddTangent(const LinearАunction& tangent,
                                           CircleObstacle& circle1,
                                           CircleObstacle& circle2) {
  std::pair<Point, Point> tangent_points =
      CrossPoints(tangent, circle1, circle2);
  tangent_points.first.another_tangent_point =
      std::make_shared<Point>(tangent_points.second);
  tangent_points.second.another_tangent_point =
      std::make_shared<Point>(tangent_points.first);
  circle1.AddTangentLine(tangent);
  circle1.AddTangentPoint(tangent_points.first);
  circle2.AddTangentLine(tangent);
  circle2.AddTangentPoint(tangent_points.second);
}

void MinimumDistanceCalculator::FillTangentsCircles() {
  for (int i = 0; i < circles_.size(); ++i) {
    for (int j = i + 1; j < circles_.size(); ++j) {
      std::vector<LinearАunction> tangents =
          TangentsBetweenCircles(circles_[i], circles_[j]);

      for (int k = 0; k < tangents.size(); ++k)
        if (!TangentGoesTroughOtherCircle(tangents[k], i, j))
          AddTangent(tangents[k], circles_[i], circles_[j]);
    }
  }
}

void MinimumDistanceCalculator::FillTangentsPoints(Point& point) {
  for (int i = 0; i < circles_.size(); ++i) {
    std::pair<Point, Point> tangent_points_1 =
        TangentPointsToCircle(circles_[i], point);
    bool is_exist_tangent1 = true;
    bool is_exist_tangent2 = true;
    for (int j = 0; j < circles_.size(); ++j) {
      if (j != i) {
        if (AreThereIntersections(circles_[j], point, tangent_points_1.first))
          is_exist_tangent1 = false;
        if (AreThereIntersections(circles_[j], point, tangent_points_1.second))
          is_exist_tangent2 = false;
      }
    }
    if (is_exist_tangent1)
      point.tangents.push_back(
          MakeLinearАunction(point, tangent_points_1.first));
    if (is_exist_tangent2)
      point.tangents.push_back(
          MakeLinearАunction(point, tangent_points_1.second));
  }
}

double MinimumDistanceCalculator::FindOptimalWay(const Point& pnt1,
                                                 const Point& pnt2) {
  FillTangentsCircles();
  FillTangentsPoints(point1_);
  FillTangentsPoints(point2_);
  PathGraph optimal_way{circles_, point1_, point2_};
}
}  // namespace math