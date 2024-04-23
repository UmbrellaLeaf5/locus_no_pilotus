#pragma once

#include "base.h"
#include "point.h"

namespace lib {

/// @brief Контрольная точка
class Target : public JSONable {
 public:
  Target(double x, double y) : p_(x, y) {}
  Target(const Point& p) : p_{p} {}
  Target() : p_(0, 0) {}

  Target(const Target&) = default;
  Target(Target&&) = default;

  Target& operator=(const Target&) = default;
  Target& operator=(Target&&) = default;

  QJsonObject GetJsonInfo(int id) const override;
  void SetJsonInfo(const QJsonObject& target_obj) override;
  bool IsChanged(const QJsonObject& target_obj) const override;

  Point GetPoint() const { return p_; }

  void SetPoint(const Point& p) { p_ = p; }
  void SetPoint(double x, double y) { p_ = Point(x, y); }

 private:
  Point p_;
};

}  // namespace lib
