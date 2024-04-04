#pragma once

#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// @brief фигура контрольной точки
class Target : public Drawable {
 public:
  Target() = default;

  Target(double x, double y) : data_(x, y) {}
  Target(lib::Point p) : data_(p) {}
  Target(lib::Target data) : data_(data) {}

  void SetPoint(lib::Point p) { data_.SetPoint(p); }
  void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  lib::Point GetPoint() const { return data_.GetPoint(); }
  lib::Target GetData() const { return data_; }

  void Draw(QCustomPlot* plot) const override;

  size_t GetPlottableIndex() { return graph_index_; }
  void SetGraphIndex(size_t index) { graph_index_ = index; }

 private:
  lib::Target data_;
  size_t graph_index_{ULLONG_MAX};
};

}  // namespace gui
