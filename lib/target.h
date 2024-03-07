#pragma once
#include "base.h"

namespace LIB {

class Target : public JSONable {
 public:
  inline Target(double x, double y) : x_{x}, y_{y} {}
  json Save() const override;
  JSONable* Load(const json& j) override;

  inline double GetX() const { return x_; }
  inline double GetY() const { return y_; }

  inline void SetX(double x) { x_ = x; }
  inline void SetY(double y) { y_ = y; }

 private:
  double x_, y_;
};

}  // namespace LIB