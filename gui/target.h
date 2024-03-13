#pragma once

#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

class Target : public Drawable {
 public:
  inline Target(double x, double y) : data_(x, y) {}
  inline Target() : data_() {}

  void Draw(QCustomPlot* plot) const override;

  inline void SetX(double x) { data_.SetX(x); }
  inline void SetY(double y) { data_.SetY(y); }

  inline double GetX() const { return data_.GetX(); }
  inline double GetY() const { return data_.GetY(); }

 private:
  lib::Target data_;
};

}  // namespace gui
