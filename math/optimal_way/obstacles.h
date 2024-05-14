#pragma once

// std libs:
#include <memory>
#include <vector>

// our code libs:
#include "lib/infinity.h"
#include "lib/point.h"

using lib::inf;
using lib::precision;

namespace math {

/// @brief Прямая вида ax+by+c=0
struct LinearFunction {
  LinearFunction(double a, double b, double c)
      : a_coef{a}, b_coef{b}, c_coef{c} {}

  LinearFunction(const lib::Point& point1, const lib::Point& point2) {
    a_coef = point2.y - point1.y;
    b_coef = -(point2.x - point1.x);
    c_coef =
        (point2.x - point1.x) * point1.y - (point2.y - point1.y) * point1.x;
  }

  double Substitute(const lib::Point& p) const {
    return a_coef * p.x + b_coef * p.y + c_coef;
  }

  double a_coef, b_coef, c_coef;

  bool operator==(const LinearFunction& other) const {
    double proportion = ((std::abs(a_coef) >= precision) &&
                         (std::abs(other.a_coef) >= precision))
                            ? other.a_coef / a_coef
                            : other.b_coef / b_coef;
    return (std::abs(other.a_coef - proportion * a_coef) < precision) &&
           (std::abs(other.b_coef - proportion * b_coef) < precision) &&
           (std::abs(other.c_coef - proportion * c_coef) < precision);
  }
};

/// @brief Точка с геометрическими связями
struct Point : public lib::Point {
  Point() = default;

  Point(const lib::Point& p) : lib::Point(p) {}

  Point(double xx, double yy) : lib::Point{xx, yy} {}

  // Вторая точка касательной
  std::shared_ptr<lib::Point> another_tangent_point = nullptr;
};

/// @brief Круговое препятствие
class CircleObstacle {
 public:
  /**
   * @brief Инициализирует экземпляр CircleObstacle
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

/// @brief Многоугольное препятствие
class PolygonObstacle {
 public:
  PolygonObstacle() = default;
  /**
   * @brief Инициализирует экземпляр PolygonObstacle
   * @param vertexes: вершины многоугольника
   */
  PolygonObstacle(const std::vector<Point>& vertexes) : vertexes_{vertexes} {
    center_ = Point(0, 0);
    for (auto& elem : vertexes_) {
      center_.x += elem.x;
      center_.y += elem.y;
    }
    center_.x /= (double)vertexes_.size();
    center_.y /= (double)vertexes_.size();
  }

  Point GetCenter() const { return center_; }

  std::vector<Point> GetVertexes() const { return vertexes_; }

  std::vector<LinearFunction> GetTangentLines() { return tangents_; }

  std::vector<Point> GetTangentPoints() { return tangent_points_; }

  void DeleteTangentPoint(std::size_t index) {
    tangent_points_.erase(tangent_points_.begin() + index);
  }

  void AddTangentLine(const LinearFunction& tangent) {
    tangents_.push_back(tangent);
  }

  void AddTangentPoint(const Point& tangent_point) {
    tangent_points_.push_back(tangent_point);
  }

  bool operator==(const PolygonObstacle& other) {
    return vertexes_ == other.vertexes_;
  }

  bool operator!=(const PolygonObstacle& other) {
    return vertexes_ != other.vertexes_;
  }

 private:
  // Геометричекий центр вершин
  Point center_;

  // Вершины
  std::vector<Point> vertexes_;

  // Касательные
  std::vector<LinearFunction> tangents_;

  // Точки касания
  std::vector<Point> tangent_points_;
};

}  // namespace math
