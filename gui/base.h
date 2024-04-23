#pragma once

#include <qcustomplot.h>

namespace gui {

/// @brief Некоторая возможная к рисованию фигура [абстрактный класс]
class Drawable {
 public:
  /**
   * @brief Привязывает (рисует) экземпляр класса на полотне
   * @param plot: указатель на соотв. полотно
   */
  virtual void Draw(QCustomPlot* plot) = 0;

  Drawable() = default;

  /**
   * @brief Возвращает индекс на полотне [plottable]
   * @return size_t: индекс
   */
  size_t GetPlottableIndex() const { return plottable_index_; }

 protected:
  void SetPlottableIndex(QCustomPlot* plot) {
    plottable_index_ = plot->plottableCount() - 1;
  }

 private:
  size_t plottable_index_{ULLONG_MAX};
};

// @brief Типы объектов по категориям
enum class ObjectType { Targets, Hills, TrappyCircles, TrappyLines };

}  // namespace gui
