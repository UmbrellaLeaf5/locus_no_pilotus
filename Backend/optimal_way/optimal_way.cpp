#include "optimal_way.h"

#include <cmath>

namespace math {

LinearАunction MinimumDistanceCalculator::MakeLinearАunction(
    const Point& point1, const Point& point2) const {
  double slope = (point2.y - point1.y) / (point2.x - point1.x);
  double b_coef = point1.y - slope * point1.x;
  return LinearАunction{slope, -1, b_coef};
}

double MinimumDistanceCalculator::DistanceBetweenPoints(const Point& p1,
                                                        const Point p2) const {
  return pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 0.5);
}

std::pair<Point, Point> MinimumDistanceCalculator::CrossPoints(
    const LinearАunction& tangent, const CircleObstacle& circle1,
    const CircleObstacle& circle2) const {
  double a = tangent.a_coef;
  double b = tangent.b_coef;
  double c = tangent.c_coef;
  double x_0 = circle1.GetCenter().x;
  double y_0 = circle1.GetCenter().y;
  double x_1 = circle2.GetCenter().x;
  double y_1 = circle2.GetCenter().y;
  double point1_x = (-((a / b) * (c / b + y_0) - x_0)) / (1 + pow(a / b, 2));
  double point1_y = a / b * point1_x - c / b;
  double point2_x = (-((a / b) * (c / b + y_1) - x_1)) / (1 + pow(a / b, 2));
  double point2_y = a / b * point2_x - c / b;
  Point point1{point1_x, point1_y};
  Point point2{point2_x, point2_y};
  return std::pair{point1, point2};
}

std::pair<Point, Point> MinimumDistanceCalculator::TangentPointsToCircle(
    const CircleObstacle& crcl, const Point& pnt) const {
  Point center = crcl.GetCenter();
  double radius = crcl.GetRadius();
  double discriminant = pow((center.x - pnt.x) * (center.y - pnt.y), 2) -
                        (pow(radius, 2) - pow(pnt.x - center.x, 2));
  double slope_1 =
      (-(center.x - pnt.x) * (center.y - pnt.y) + sqrt(discriminant)) /
      (pow(radius, 2) - pow(pnt.x - center.x, 2));
  double slope_2 =
      (-(center.x - pnt.x) * (center.y - pnt.y) - sqrt(discriminant)) /
      (pow(radius, 2) - pow(pnt.x - center.x, 2));
  double b1_coef = pnt.y - slope_1 * pnt.x;
  double b2_coef = pnt.y - slope_2 * pnt.x;
  double x1_cross_pnt = (-(slope_1 * b1_coef - center.x - slope_1 * center.y)) /
                        (1 + pow(slope_1, 2));
  double x2_cross_pnt = (-(slope_2 * b2_coef - center.x - slope_2 * center.y)) /
                        (1 + pow(slope_2, 2));
  double y1_cross_pnt = slope_1 * x1_cross_pnt + b1_coef;
  double y2_cross_pnt = slope_2 * x2_cross_pnt + b2_coef;
  return std::pair<Point, Point>{{x1_cross_pnt, y1_cross_pnt},
                                 {x2_cross_pnt, y2_cross_pnt}};
}

std::vector<LinearАunction> MinimumDistanceCalculator::TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2) const {
  std::vector<LinearАunction> tangents;
  double x_1 = circle2.GetCenter().x;
  double y_1 = circle2.GetCenter().y;
  double r_1 = circle2.GetRadius();
  double x_0 = circle1.GetCenter().x;
  double y_0 = circle1.GetCenter().y;
  double r_0 = circle1.GetRadius();

  auto FindTangent = [&x_1, &x_0, &y_1, &y_0](double r_0, double r_1) {
    double b =
        ((r_1 - r_0) * (y_1 - y_0) +
         sqrt(pow(x_1 - x_0, 2) *
              (pow(x_1 - x_0, 2) + pow(y_1 - y_0, 2) - pow(r_1 - r_0, 2)))) /
        (pow(x_1 - x_0, 2) + pow(y_1 - y_0, 2));
    double a = ((r_1 - r_0) - b * (y_1 - y_0)) / (x_1 - x_0);
    double c = r_0 - a * x_0 - b * y_0;
    LinearАunction tangent{a, b, c};
    return tangent;
  };

  for (auto n1 : {-1, 1})
    for (auto n2 : {-1, 1}) tangents.push_back(FindTangent(r_0 * n1, r_1 * n2));
  return tangents;
}

bool MinimumDistanceCalculator::AreThereIntersections(
    const CircleObstacle& crcl, const Point& pnt1, const Point& pnt2) const {
  double slope = (point2_.y - point1_.y) / (point2_.x - point1_.x);
  double b_coef = point1_.y - slope * point1_.x;
  Point center = crcl.GetCenter();
  double radius = crcl.GetRadius();
  double discriminant = (pow(slope * b_coef - center.x - slope * center.y, 2)) +
                        (pow(radius, 2) - pow(center.x, 2) - pow(b_coef, 2) -
                         pow(center.y, 2) + 2 * b_coef * center.y) *
                            (1 + pow(slope, 2));
  if (discriminant <= 0)
    return false;
  else {
    float x_1 =
        (-(slope * b_coef - center.x - slope * center.y) + sqrt(discriminant)) /
        (1 + pow(slope, 2));
    float x_2 =
        (-(slope * b_coef - center.x - slope * center.y) - sqrt(discriminant)) /
        (1 + pow(slope, 2));
    if ((std::min(point1_.x, point2_.x) <= x_1 <=
         std::max(point1_.x, point2_.x)) ||
        (std::min(point1_.x, point2_.x) <= x_2 <=
         std::max(point1_.x, point2_.x)))
      return true;
    else
      return false;
  }
}

void MinimumDistanceCalculator::FillTangentsCircles() {
  for (int i = 0; i < circles_.size(); ++i) {
    for (int j = i + 1; j < circles_.size(); ++j) {
      std::vector<LinearАunction> tangents =
          TangentsBetweenCircles(circles_[i], circles_[j]);
      for (int k = 0; k < tangents.size(); ++k) {
        bool is_exist = true;
        for (int l = 0; l < circles_.size(); ++l) {
          if (l != i && l != j) {
            std::pair<Point, Point> tangent_points =
                CrossPoints(tangents[k], circles_[i], circles_[j]);
            if (AreThereIntersections(circles_[l], tangent_points.first,
                                      tangent_points.second)) {
              is_exist = false;
              break;
            }
          }
        }
        if (is_exist) {
          std::pair<Point, Point> tangent_points =
              CrossPoints(tangents[k], circles_[i], circles_[j]);
          tangent_points.first.another_tangent_point =
              std::make_shared<Point>(tangent_points.second);
          tangent_points.second.another_tangent_point =
              std::make_shared<Point>(tangent_points.first);
          circles_[i].AddTangentLine(tangents[k]);
          circles_[i].AddTangentPoint(tangent_points.first);
          circles_[j].AddTangentLine(tangents[k]);
          circles_[j].AddTangentPoint(tangent_points.second);
        }
      }
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
