#pragma once

#include <memory>
#include <vector>

#include "../lib/point.h"

namespace math {

// Структура хранит коэфиценты для прямой вида ax+by+c=0
struct LinearАunction {
  LinearАunction(double a, double b, double c)
      : a_coef{a}, b_coef{b}, c_coef{c} {}
  double a_coef, b_coef, c_coef;
  bool operator==(const LinearАunction& other) {
    return (a_coef == other.a_coef && b_coef == other.b_coef &&
            c_coef == other.c_coef);
  }
};

struct Point : public lib::Point {
  Point(double xx, double yy) : lib::Point{xx, yy} {}
  std::vector<LinearАunction> tangents;
  std::shared_ptr<Point> another_tangent_point = nullptr;
};

class CircleObstacle {
 public:
  CircleObstacle(Point center, double radius)
      : center_{center}, radius_{radius} {}
  CircleObstacle() : center_{0, 0}, radius_{0} {}

  Point GetCenter() const { return center_; }
  double GetRadius() const { return radius_; }
  std::vector<LinearАunction> GetTangentLines() { return tangents_; }
  std::vector<Point> GetTangentPoints() { return tangent_points_; }

  void SetCenter(const Point& center) { center_ = center; }
  void SetRadius(double r) { radius_ = r; }
  void AddTangentLine(const LinearАunction& tangent) {
    tangents_.push_back(tangent);
  }
  void AddTangentPoint(const Point& tangent_point) {
    tangent_points_.push_back(tangent_point);
  }
  bool operator==(const CircleObstacle& other) {
    return (center_ == other.center_ && radius_ == other.radius_);
  }

 private:
  Point center_;
  double radius_;
  std::vector<LinearАunction> tangents_;
  std::vector<Point> tangent_points_;
};
}  // namespace math
