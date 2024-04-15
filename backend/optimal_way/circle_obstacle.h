#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include "../lib/point.h"

namespace math {

constexpr double precision = lib::precision;

/// @brief прямая вида ax+by+c=0
struct LinearFunction {
  LinearFunction(double a, double b, double c)
      : a_coef{a}, b_coef{b}, c_coef{c} {}

  double a_coef, b_coef, c_coef;

  bool operator==(const LinearFunction& other) {
    return (std::abs(a_coef - other.a_coef) < precision &&
            std::abs(b_coef - other.b_coef) < precision &&
            std::abs(c_coef - other.c_coef) < precision);
  }
};

/// @brief точка с геометрическими связями
struct Point : public lib::Point {
  Point(double xx, double yy) : lib::Point{xx, yy} {}

  // Касательные, проходящие через точку
  std::vector<LinearFunction> tangents;

  // Вторая точка касательной
  std::shared_ptr<Point> another_tangent_point = nullptr;
};

/// @brief круговое препятствие
class CircleObstacle {
 public:
  /**
   * @brief инициалирует экземпляр CircleObstacle
   * @param center: центр круга
   * @param radius: радиус круга
   */
  CircleObstacle(Point center, double radius)
      : center_{center}, radius_{radius} {}

  CircleObstacle() : center_{0, 0}, radius_{0} {}

  Point GetCenter() const { return center_; }

  double GetRadius() const { return radius_; }

  std::vector<LinearFunction> GetTangentLines() { return tangents_; }

  std::vector<Point> GetTangentPoints() { return tangent_points_; }

  void SetCenter(const Point& center) { center_ = center; }

  void SetRadius(double r) { radius_ = r; }

  void AddTangentLine(const LinearFunction& tangent) {
    tangents_.push_back(tangent);
  }

  void AddTangentPoint(const Point& tangent_point) {
    tangent_points_.push_back(tangent_point);
  }

  bool operator==(const CircleObstacle& other) {
    return (center_ == other.center_ &&
            std::abs(radius_ - other.radius_) < precision);
  }

  bool operator!=(const CircleObstacle& other) {
    return (center_ != other.center_ ||
            std::abs(radius_ - other.radius_) >= precision);
  }

 private:
  Point center_;

  double radius_;

  // Касательные
  std::vector<LinearFunction> tangents_;

  // Точки касания
  std::vector<Point> tangent_points_;
};

}  // namespace math
