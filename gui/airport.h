#pragma once

// our code libs:
#include "target.h"  // base class

namespace gui {

/**
 * @brief Фигура контрольной точки, откуда происходит запуск
 * @details По сути является модификацией gui::Target
 * с переопределенным методом Draw(QCustomPlot* plot).
 * Фигура представляет собой черную окружность (точку) с крестом
 */
class Airport : public gui::Target {
 public:
  Airport() : Target() {}

  Airport(double x, double y) : Target(x, y) {}
  Airport(lib::Point p) : Target(p) {}
  Airport(const lib::Target& data) : Target(data) {}

  Airport(const Target& t) : Target(t) {}
  Airport(Target&& t) : Target(t) {}

  /**
   * @brief Отрисовывает фигуру на полотне
   * @details Фигура представляет собой черную окружность (точку) с крестом
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;
};

inline void gui::Airport::Draw(QCustomPlot* plot) {
  Target::Draw(plot);
  auto graph = Target::GetGraphPtr();

  graph->setPen(QColor(0, 0, 0, 255));
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
}

}  // namespace gui