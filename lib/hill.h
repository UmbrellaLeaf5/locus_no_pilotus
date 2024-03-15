#pragma once

#include "base.h"
#include "point.h"

namespace lib {

// MEANS: рельеф с высотой
class Hill : public JSONable {
 public:
  Hill(Point center = {0, 0}, double radius = 0)
      : center_{center}, radius_{radius} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline Point GetCenter() const { return center_; }
  inline double GetRadius() const { return radius_; }

  inline void SetCenter(const Point& center) { center_ = center; }
  inline void SetRadius(double r) { radius_ = r; }

 private:
  Point center_;
  double radius_;
};

}  // namespace lib
