#pragma once

#include <cmath>

#include "infinity.h"

namespace lib {

constexpr double precision = 1.0E-6;

/// @brief Математическая точка
struct Point {
  double x;
  double y;

  Point(double x = 0, double y = 0) : x{x}, y{y} {}

  Point(const Point& p) = default;

  Point& operator=(const Point& p) = default;

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

/**
 * @brief Оператор сравнения двух точек
 * @details Работает как примерно равно (с точностью precision = 1.0E-6)
 * @param a: первая точка
 * @param b: вторая точка
 * @return true: если точки примерно равны
 * @return false: если точки не равны даже примерно
 */
inline bool operator==(Point a, Point b) {
  return std::abs(a.x - b.x) < precision && std::abs(a.y - b.y) < precision;
}

inline bool operator!=(Point a, Point b) { return !(a == b); }

}  // namespace lib

/**
 * @brief Проверяет, является ли точка бесконечной
 * (имеет именование в стиле стандартной функции)
 * @param p: точка
 * @return true: если является
 * @return false: если не является
 */
inline bool isinf(const lib::Point& p) {
  return std::isinf(p.x) || std::isinf(p.y);
}
