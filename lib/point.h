#pragma once

namespace lib {

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
};

inline Point operator+(Point a, Point b) { return a += b; }
inline Point operator-(Point a, Point b) { return a -= b; }

inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
inline bool operator!=(Point a, Point b) { return !(a == b); }

}  // namespace lib
