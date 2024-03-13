#pragma once
#include "base.h"

namespace lib {

class Target : public JSONable {
 public:
  inline Target(double x, double y) : p_{lib::Point(x, y)} {}
  inline Target(const Point& p) : p_{p} {}
  inline Target() : p_{Point()} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline Point GetPoint() const { return p_; }

  inline void SetPoint(const Point& p) { p_ = p; }

 private:
  Point p_;
};

}  // namespace lib