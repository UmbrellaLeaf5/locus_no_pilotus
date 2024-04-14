#pragma once

#include "base.h"
#include "lib/target.h"

namespace gui {

/// @brief фигура контрольной точки
class Target : public Drawable {
 public:
  Target() = default;

  Target(double x, double y) : data_(x, y) {}
  Target(lib::Point p) : data_(p) {}
  Target(const lib::Target& data) : data_(data) {}

  Target(const Target&) = default;
  Target(Target&&) = default;

  Target& operator=(const Target&) = default;
  Target& operator=(Target&&) = default;

  void SetPoint(lib::Point p) { data_.SetPoint(p); }
  void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  lib::Point GetPoint() const { return data_.GetPoint(); }
  lib::Target GetData() const { return data_; }

  void Draw(QCustomPlot* plot) override;

  /**
   * @brief возвращает индекс на полотне [plottable]
   * @return size_t: индекс
   */
  size_t GetPlottableIndex() const { return plottable_index_; }

  /**
   * @brief возвращает значение указателя на полотне
   * @return QCPGraph*: указатель
   */
  QCPGraph* GetGraphPtr() const { return graph_; }

 private:
  lib::Target data_;
  size_t plottable_index_{ULLONG_MAX};
  QCPGraph* graph_{nullptr};
};

}  // namespace gui
