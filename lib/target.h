#pragma once

#include "base.h"
#include "point.h"

namespace lib {

// MEANS: контрольная точка
class Target : public JSONable {
 public:
  inline Target(double x, double y) : p_(x, y) {}
  inline Target(const Point& p) : p_{p} {}
  inline Target() : p_(0, 0) {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline Point GetPoint() const { return p_; }

  inline void SetPoint(const Point& p) { p_ = p; }
  inline void SetPoint(double x, double y) { p_ = Point(x, y); }

 private:
  Point p_;
};

}  // namespace lib
