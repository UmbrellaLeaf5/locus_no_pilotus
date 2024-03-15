#pragma once

using json = void*;

namespace lib {

class JSONable {
 public:
  // JSONable(const json& j);

  virtual json Save() const = 0;
  virtual JSONable* Load(const json& j) = 0;
};

struct Point {
  double x;
  double y;

  Point(double x = 0, double y = 0) : x{x}, y{y} {}

  Point(const Point& p) : x{p.x}, y{p.y} {}

  inline Point& operator=(const Point& p) {
    x = p.x;
    y = p.y;
    return *this;
  }

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
