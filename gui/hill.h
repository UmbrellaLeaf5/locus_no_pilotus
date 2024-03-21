#pragma once

#include "../lib/hill.h"
#include "base.h"
#include "qcustomplot.h"
#include "trappy_circle.h"

namespace gui {

// MEANS: фигура рельефа с высотой
class Hill : public TrappyCircle {
 public:
  // конструктора по умолчанию быть не может, так как
  // рельеф должен быть отрисован в конкретном месте

  inline Hill(double x, double y, double radius,
              QColor color = QColor(50, 200, 50, 255))
      : TrappyCircle(x, y, radius, color) {}

  inline Hill(lib::Point center, double radius,
              QColor color = QColor(50, 200, 50, 255))
      : TrappyCircle(center, radius, color) {}

 private:
};

}  // namespace gui
