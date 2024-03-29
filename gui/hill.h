#pragma once

#include <initializer_list>
#include <vector>

#include "../lib/hill.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// @brief фигура рельефа с высотой
class Hill : public Drawable {
 public:
  Hill() = default;

  /**
   * @brief инициализирует новый экземпляр Hill
   *
   * @param center центр описанной окружности
   * @param radius радиус опис. окр.
   * @param vertices_amount кол-во вершин
   * @param color цвет
   */
  Hill(lib::Point center, double radius, std::size_t vertices_amount,
       QColor color = QColor(50, 200, 50, 255))
      : data_(center, radius, vertices_amount), color_{color} {}

  /**
   * @brief инициализирует новый экземпляр Hill
   *
   * @param points список точек
   * @param color цвет
   */
  Hill(std::initializer_list<lib::Point> points,
       QColor color = QColor(50, 200, 50, 255))
      : data_(points), color_{color} {}

  lib::Point GetCenter() const;
  double GetRadius() const;

  void Draw(QCustomPlot* plot) const override;

 private:
  lib::Hill data_;
  QColor color_;
};

}  // namespace gui
