#pragma once

#include "target.h"

namespace gui {

/// @brief Фигура контрольной точки, откуда происходит запуск
class Airport : public gui::Target {
 public:
  Airport() : Target() {}

  Airport(double x, double y) : Target(x, y) {}
  Airport(lib::Point p) : Target(p) {}
  Airport(const lib::Target& data) : Target(data) {}

  Airport(const Target& t) : Target(t) {}
  Airport(Target&& t) : Target(t) {}

  /// @details Фигура представляет собой малую серую окружность (точку)
  void Draw(QCustomPlot* plot) override;
};

inline void gui::Airport::Draw(QCustomPlot* plot) {
  Target::Draw(plot);
  auto graph = Target::GetGraphPtr();

  graph->setPen(QColor(0, 0, 0, 255));
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
}

}  // namespace gui