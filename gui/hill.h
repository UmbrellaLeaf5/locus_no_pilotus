#pragma once

#include <initializer_list>
#include <vector>

#include "../lib/hill.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

// MEANS: фигура рельефа с высотой
class Hill : public Drawable {
 public:
  // конструктора по умолчанию быть не может, так как
  // рельеф должен быть отрисован в конкретном месте

  // MEANS: конструктор правильного многоугольного рельефа
  // ARGS: [lib::Point]: центр описанной окружности;
  // ARGS: [double]: радиус опис. окр.; [size_t]: кол-во вершин
  Hill(lib::Point center, double radius, std::size_t vertices_amount,
       QColor color = QColor(50, 200, 50, 255))
      : data_(center, radius, vertices_amount), color_{color} {}

  // MEANS: конструктор многоугольного рельефа (по точкам)
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
