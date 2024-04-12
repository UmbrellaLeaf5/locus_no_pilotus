#pragma once

#include <qcustomplot.h>

#include "../lib/trappy_circle.h"
#include "base.h"

namespace gui {

/// @brief фигура опасной зоны
class TrappyCircle : public Drawable {
 public:
  TrappyCircle() = default;

  TrappyCircle(double x, double y, double radius,
               QColor color = QColor(200, 50, 50, 255))
      : data_(lib::Point{x, y}, radius), color_{color} {}

  TrappyCircle(lib::Point center, double radius,
               QColor color = QColor(200, 50, 50, 255))
      : data_(center, radius), color_{color} {}

  TrappyCircle(const lib::TrappyCircle& data,
               QColor color = QColor(200, 50, 50, 255))
      : data_(data), color_{color} {}

  TrappyCircle(const TrappyCircle&) = default;
  TrappyCircle(TrappyCircle&&) = default;

  TrappyCircle& operator=(const TrappyCircle&) = default;
  TrappyCircle& operator=(TrappyCircle&&) = default;

  lib::Point GetCenter() const { return data_.GetCenter(); }
  double GetRadius() const { return data_.GetRadius(); }
  QColor GetColor() const { return color_; }
  lib::TrappyCircle GetData() const { return data_; }

  void SetCenter(const lib::Point& center) { data_.SetCenter(center); }
  void SetRadius(double radius) { data_.SetRadius(radius); }

  void Draw(QCustomPlot* plot) const override;

  size_t GetItemIndex() const { return item_index_; }
  void SetItemIndex(size_t index) { item_index_ = index; }

 private:
  lib::TrappyCircle data_;
  QColor color_;
  size_t item_index_;
};

}  // namespace gui
