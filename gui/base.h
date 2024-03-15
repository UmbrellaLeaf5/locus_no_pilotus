#pragma once

#include "qcustomplot.h"

namespace gui {

// MEANS: некоторая возможная к рисованию фигура [абстрактный класс]
class Drawable {
 public:
  // DOES: привязывает (рисует) экземпляр класса на полотне
  // ARGS: [QCustomPlot*]: указатель на соотв. полотно
  virtual void Draw(QCustomPlot* plot) const = 0;
};

}  // namespace gui
