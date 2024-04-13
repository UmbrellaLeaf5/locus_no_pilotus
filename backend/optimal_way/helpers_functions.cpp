#include "helpers_functions.h"

#include <cmath>

namespace math {
LinearАunction MakeLinearАunction(const Point& point1, const Point& point2) {
  double slope = (point2.y - point1.y) / (point2.x - point1.x);
  double b_coef = point1.y - slope * point1.x;
  return LinearАunction{slope, -1, b_coef};
}

double DistanceBetweenPoints(const Point& p1, const Point& p2) {
  return pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 0.5);
}

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2) {
  double line = DistanceBetweenPoints(p1, p2);
  double cos_alpha = (pow(line, 2) - 2 * pow(circle.GetRadius(), 2)) /
                     (2 * circle.GetRadius());
  return circle.GetRadius() * acos(cos_alpha);
}

std::pair<Point, Point> CrossPoints(const LinearАunction& tangent,
                                    const CircleObstacle& circle1,
                                    const CircleObstacle& circle2) {
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

std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& crcl,
                                              const Point& pnt) {
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

std::vector<LinearАunction> TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2) {
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

bool AreThereIntersections(const CircleObstacle& crcl, const Point& point1,
                           const Point& point2) {
  double slope = (point2.y - point1.y) / (point2.x - point1.x);
  double b_coef = point1.y - slope * point1.x;
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
    if ((std::min(point1.x, point2.x) <= x_1 <= std::max(point1.x, point2.x)) ||
        (std::min(point1.x, point2.x) <= x_2 <= std::max(point1.x, point2.x)))
      return true;
    else
      return false;
  }
}
}  // namespace math
