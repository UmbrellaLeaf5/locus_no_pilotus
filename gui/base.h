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
  virtual size_t GetIndexOnPlot() const { return index_on_plot_; }

 protected:
  virtual void SetIndexOnPlot(QCustomPlot* plot) {
    index_on_plot_ = plot->plottableCount() - 1;
  }

 private:
  size_t index_on_plot_{ULLONG_MAX};
};

// @brief Типы объектов по категориям
enum class ObjectType { Targets, Hills, TrappyCircles, TrappyLines };

}  // namespace gui
