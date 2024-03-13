#pragma once

#include "../lib/base.h"
#include "../lib/trappy_circle.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {
class TrappyCircle : public Drawable {
 public:
  inline TrappyCircle(double x, double y, double radius)
      : trc_{lib::TrappyCircle{lib::Point{x, y}, radius}} {}

  inline TrappyCircle(lib::Point center, double radius)
      : trc_{lib::TrappyCircle{center, radius}} {}

  inline lib::Point GetCenter() const { return trc_.GetCenter(); }
  inline double GetRadius() const { return trc_.GetRadius(); }

  inline void SetCenter(const lib::Point& center) { trc_.SetCenter(center); }
  inline void SetRad(double radius) { trc_.SetRadius(radius); }

  void Draw(QCustomPlot* plot) const override;

 private:
  lib::TrappyCircle trc_;
};
}  // namespace gui
