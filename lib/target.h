#pragma once
#include "base.h"

namespace LIB {

class Target : public JSONable {
 public:
  inline Target(double x, double y) : x_{x}, y_{y} {}
  json save() const override;
  JSONable load(const json& j) override;

 private:
  double x_, y_;
};

}  // namespace LIB