#pragma once

#include <cmath>

#include "infinity.h"

namespace lib {

constexpr double precision = 1.0E-6;

// MARK: Point

/// @brief Математическая точка
struct Point {
  double x;
  double y;

  Point(double x = 0, double y = 0) : x{x}, y{y} {}

  Point(const Point& point) = default;

  Point& operator=(const Point& point) = default;

  Point& operator+=(const Point& d) {
    x += d.x;
    y += d.y;
    return *this;
  }

  Point& operator-=(const Point& d) {
    x -= d.x;
    y -= d.y;
    return *this;
  }

  const static Point InfPoint() { return {inf, inf}; }
};

inline Point operator+(Point a, Point b) { return a += b; }
inline Point operator-(Point a, Point b) { return a -= b; }

bool operator==(Point a, Point b);

inline bool operator!=(Point a, Point b) { return !(a == b); }

double DistanceBetweenPoints(const Point& first_point,
                             const Point& second_point);

// MARK: PointAsAngles

/**
 * @brief Математическая точка на ед. окружности, выраженная в градусах
 * @details Имеет два поля, представляющие собой углы
 * на промежутках [0°; 360°] и [-360°; 0°]
 */
struct PointAsAngles {
  /// @brief Угол на промежутке [0°; 360°]
  double positive_angle;

  /// @brief Угол на промежутке [-360°; 0°]
  double negative_angle;

  PointAsAngles(double positive_angle = 0, double negative_angle = 0);

  /**
   * @brief Переводит lib::PointAsAngles в std::pair
   * @return std::pair<double, double>: пара углов
   */
  std::pair<double, double> ToPair() {
    return std::make_pair(positive_angle, negative_angle);
  }

  static PointAsAngles FromPoint(const lib::Point& point,
                                 const lib::Point& center);

  const static PointAsAngles InfPoint() { return {inf, inf}; }
};

// MARK: CircleQuadrant

/// @brief Четверть мат. окружности
enum class CircleQuadrant { First, Second, Third, Fourth };

CircleQuadrant QuadrantOccupiedByPoint(const lib::Point& point,
                                       const lib::Point& center);

}  // namespace lib

// MARK: isinf

/**
 * @brief Проверяет, является ли точка бесконечной
 * (имеет именование в стиле стандартной функции)
 * @param point: точка
 * @return true: если является
 * @return false: если не является
 */
inline bool isinf(const lib::Point& point) {
  return std::isinf(point.x) || std::isinf(point.y);
}

/**
 * @brief Проверяет, является ли точка бесконечной
 * (имеет именование в стиле стандартной функции)
 * @param point: точка на ед. окружности
 * @return true: если является
 * @return false: если не является
 */
inline bool isinf(const lib::PointAsAngles& point) {
  return std::isinf(point.positive_angle) || std::isinf(point.negative_angle);
}
