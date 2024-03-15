#pragma once

#include "../lib/hill.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// MEANS: фигура рельефа с высотой
class Hill : public Drawable {
 public:
  // конструктора по умолчанию быть не может, так как
  // рельеф должен быть отрисован в конкретном месте

  inline Hill(double x, double y, double radius)
      : data_(lib::Point{x, y}, radius) {}

  inline Hill(lib::Point center, double radius) : data_(center, radius) {}

  inline lib::Point GetCenter() const { return data_.GetCenter(); }
  inline double GetRadius() const { return data_.GetRadius(); }

  inline void SetCenter(const lib::Point& center) { data_.SetCenter(center); }
  inline void SetRadius(double radius) { data_.SetRadius(radius); }

  void Draw(QCustomPlot* plot) const override;

 private:
  lib::Hill data_;
};

}  // namespace gui
