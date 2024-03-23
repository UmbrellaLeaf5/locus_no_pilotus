#pragma once

#include "base.h"
#include "point.h"

namespace lib {

// MEANS: опасная зона
class TrappyCircle : public JSONable {
 public:
  TrappyCircle(Point center = {0, 0}, double radius = 0)
      : center_{center}, radius_{radius} {}

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
