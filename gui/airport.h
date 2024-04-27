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

  void Draw(QCustomPlot* plot) override;
};

}  // namespace gui