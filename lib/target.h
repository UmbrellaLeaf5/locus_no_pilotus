#pragma once
#include "base.h"

namespace lib {

class Target : public JSONable {
 public:
  inline Target(double x, double y) : x_{x}, y_{y} {}
  inline Target() : x_{0}, y_{0} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline double GetX() const { return x_; }
  inline double GetY() const { return y_; }

  inline void SetX(double x) { x_ = x; }
  inline void SetY(double y) { y_ = y; }

 private:
  double x_, y_;
};

}  // namespace lib