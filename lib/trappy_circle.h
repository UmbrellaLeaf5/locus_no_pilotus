#pragma once

#include <stdexcept>

#include "base.h"
#include "point.h"

namespace lib {

// @brief опасная зона
class TrappyCircle : public JSONable {
 public:
  TrappyCircle(Point center = {0, 0}, double radius = 0);

  TrappyCircle(const TrappyCircle&) = default;
  TrappyCircle(TrappyCircle&&) = default;

  TrappyCircle& operator=(const TrappyCircle&) = default;
  TrappyCircle& operator=(TrappyCircle&&) = default;

  QJsonObject Save(int id) const override;
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
