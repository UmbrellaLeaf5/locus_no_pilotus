#pragma once

#include "../lib/base.h"
#include "../lib/hill.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {
class Hill : public Drawable {
 public:
  inline Hill(double x, double y, double radius)
      : hill_{lib::Hill{lib::Point{x, y}, radius}} {}

  inline Hill(lib::Point center, double radius)
      : hill_{lib::Hill{center, radius}} {}

  inline lib::Point GetCenter() const { return hill_.GetCenter(); }
  inline double GetRadius() const { return hill_.GetRadius(); }

  inline void SetCenter(const lib::Point& center) { hill_.SetCenter(center); }
  inline void SetRad(double radius) { hill_.SetRadius(radius); }

  void Draw(QCustomPlot* plot) const override;

 private:
  lib::Hill hill_;
};
}  // namespace gui
