#pragma once

#include "../lib/base.h"
#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

class Target : public Drawable {
 public:
  inline Target(double x, double y) : data_(x, y) {}
  inline Target(lib::Point p) : data_(p) {}
  inline Target() : data_() {}

  void Draw(QCustomPlot* plot) const override;

  inline void SetPoint(lib::Point p) { data_.SetPoint(p); }
  inline void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  inline lib::Point GetPoint() const { return data_.GetPoint(); }

  inline lib::Target GetData() const { return data_; }

 private:
  lib::Target data_;
};

}  // namespace gui
