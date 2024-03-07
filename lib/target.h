#pragma once
#include "base.h"

namespace LIB {

class Target : public JSONable {
 public:
  inline Target(double x, double y) : x_{x}, y_{y} {}
  json save() const override;
  JSONable* load(const json& j) override;

  inline double getX() const { return x_; }
  inline double getY() const { return y_; }

  inline void setX(double x) { x_ = x; }
  inline void setY(double y) { y_ = y; }

 private:
  double x_, y_;
};

}  // namespace LIB