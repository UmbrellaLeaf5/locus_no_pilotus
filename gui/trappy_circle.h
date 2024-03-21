#pragma once

#include "../lib/trappy_circle.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// MEANS: фигура опасной зоны
class TrappyCircle : public Drawable {
 public:
  // конструктора по умолчанию быть не может, так как
  // опасная зона должна быть отрисована в конкретном месте

  inline TrappyCircle(double x, double y, double radius,
                      QColor color = QColor(200, 50, 50, 255))
      : data_(lib::Point{x, y}, radius), color_{color} {}

  inline TrappyCircle(lib::Point center, double radius,
                      QColor color = QColor(200, 50, 50, 255))
      : data_(center, radius), color_{color} {}

  inline lib::Point GetCenter() const { return data_.GetCenter(); }
  inline double GetRadius() const { return data_.GetRadius(); }

  inline void SetCenter(const lib::Point& center) { data_.SetCenter(center); }
  inline void SetRadius(double radius) { data_.SetRadius(radius); }

  void Draw(QCustomPlot* plot) const override;

 private:
  lib::TrappyCircle data_;
  QColor color_;
};

}  // namespace gui
