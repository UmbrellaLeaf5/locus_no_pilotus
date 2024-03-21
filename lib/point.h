#pragma once

namespace lib {

struct Point {
  double x;
  double y;

  inline Point(double x = 0, double y = 0) : x{x}, y{y} {}

  inline Point(const Point& p) = default;

  inline Point& operator=(const Point& p) = default;

  inline Point& operator+=(const Point& d) {
    x += d.x;
    y += d.y;
    return *this;
  }

  inline Point& operator-=(const Point& d) {
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
