#pragma once

#include <stdexcept>

#include "base.h"
#include "point.h"

namespace lib {

// @brief опасная зона
class TrappyCircle : public JSONable {
 public:
  TrappyCircle(Point center = {0, 0}, double radius = 0)
      : center_{center}, radius_{radius} {
    if (radius < 0)
      throw std::invalid_argument(
          "trappy circle cannot have of negative radius");
  }

  json Save() const override;
  JSONable* Load(const json& j) override;

  Point GetCenter() const { return center_; }
  double GetRadius() const { return radius_; }

  void SetCenter(const Point& center) { center_ = center; }
  void SetRadius(double r) { radius_ = r; }

 private:
  Point center_;
  double radius_;
};

}  // namespace lib
