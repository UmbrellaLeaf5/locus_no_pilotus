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
  virtual void Draw(QCustomPlot* plot) = 0;

  Drawable() = default;
};

// @brief типы объектов по категориям
enum class ObjectType { Targets, Hills, TrappyCircles, TrappyLines };

}  // namespace gui
