#pragma once

#include "qcustomplot.h"

namespace gui {
class Drawable {
 public:
  virtual void Draw(QCustomPlot* plot) const = 0;
};

}  // namespace gui
