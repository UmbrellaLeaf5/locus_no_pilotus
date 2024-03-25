#pragma once

#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// @brief фигура контрольной точки
class Target : public Drawable {
 public:
  Target() = default;

  Target(double x, double y) : data_(x, y) {}
  Target(lib::Point p) : data_(p) {}

  void Draw(QCustomPlot* plot) const override;

  void SetPoint(lib::Point p) { data_.SetPoint(p); }
  void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  lib::Point GetPoint() const { return data_.GetPoint(); }

  lib::Target GetData() const { return data_; }

 private:
  lib::Target data_;
};

}  // namespace gui
