#pragma once

#include <qcustomplot.h>

#include <initializer_list>
#include <vector>

#include "../lib/hill.h"
#include "base.h"

namespace gui {

/// @brief фигура рельефа с высотой
class Hill : public Drawable {
 public:
  Hill() = default;

  /**
   * @brief инициализирует новый экземпляр Hill
   * @param center: центр описанной окружности
   * @param radius: радиус опис. окр.
   * @param vertices_amount: кол-во вершин
   * @param color: цвет
   */
  Hill(lib::Point center, double radius, std::size_t vertices_amount,
       QColor color = QColor(50, 200, 50, 255))
      : data_(center, radius, vertices_amount), color_{color} {}

  /**
   * @brief инициализирует новый экземпляр Hill
   * @param points: список точек
   * @param color: цвет
   */
  Hill(std::initializer_list<lib::Point> points,
       QColor color = QColor(50, 200, 50, 255))
      : data_(points), color_{color} {}

  Hill(std::vector<lib::Point> points, QColor color = QColor(50, 200, 50, 255))
      : data_(points), color_{color} {}

  Hill(lib::Hill data, QColor color = QColor(50, 200, 50, 255))
      : data_(data), color_{color} {}

  lib::Point GetCenter() const { return data_.GetCenter(); }
  double GetRadius() const { return data_.GetRadius(); }
  lib::Hill GetData() const { return data_; }

  std::vector<lib::Point> GetPoints() const { return data_.GetPoints(); }

  void Draw(QCustomPlot* plot) const override;

  size_t GetPlottableIndex() { return graph_index_; }
  void SetGraphIndex(size_t index) { graph_index_ = index; }

 private:
  lib::Hill data_;
  QColor color_;
  size_t graph_index_{ULLONG_MAX};
};

}  // namespace gui
