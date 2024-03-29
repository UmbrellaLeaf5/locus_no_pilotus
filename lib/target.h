#pragma once

#include "base.h"
#include "point.h"

namespace lib {

// @brief контрольная точка
class Target : public JSONable {
 public:
  Target(double x, double y) : p_(x, y) {}
  Target(const Point& p) : p_{p} {}
  Target() : p_(0, 0) {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  Point GetPoint() const { return p_; }

  void SetPoint(const Point& p) { p_ = p; }
  void SetPoint(double x, double y) { p_ = Point(x, y); }

 private:
  Point p_;
};

}  // namespace lib
