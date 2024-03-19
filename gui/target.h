#pragma once

#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// MEANS: фигура контрольной точки
class Target : public Drawable {
 public:
  // конструктора по умолчанию быть не может, так как
  // КТ должна быть отрисована в конкретном месте

  inline Target(double x, double y) : data_(x, y) {}
  inline Target(lib::Point p) : data_(p) {}

  void Draw(QCustomPlot* plot) const override;

  inline void SetPoint(lib::Point p) { data_.SetPoint(p); }
  inline void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  inline lib::Point GetPoint() const { return data_.GetPoint(); }

  inline lib::Target GetData() const { return data_; }

 private:
  lib::Target data_;
};

}  // namespace gui
