#pragma once

#include <qcustomplot.h>

namespace gui {

/// @brief некоторая возможная к рисованию фигура [абстрактный класс]
class Drawable {
 public:
  /**
   * @brief привязывает (рисует) экземпляр класса на полотне
   * @param plot: указатель на соотв. полотно
   */
  virtual void Draw(QCustomPlot* plot) const = 0;
};

// @brief типы объектов по категориям
enum class GuiObjType { Targets, Hills, TrappyCircles, TrappyLines };

}  // namespace gui
