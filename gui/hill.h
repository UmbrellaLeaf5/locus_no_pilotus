#pragma once

#include "base.h"
#include "lib/hill.h"

namespace gui {

/// @brief Фигура рельефа с высотой
class Hill : public Drawable {
 public:
  Hill() = default;

  /**
   * @brief Инициализирует новый экземпляр Hill
   * @param center: центр описанной окружности
   * @param radius: радиус опис. окр.
   * @param vertices_amount: кол-во вершин
   * @param color: цвет
   */
  Hill(lib::Point center, double radius, std::size_t vertices_amount,
       QColor color = QColor(50, 200, 50, 255))
      : data_(center, radius, vertices_amount), color_{color} {}

  /**
   * @brief Инициализирует новый экземпляр Hill
   * @param points: список точек
   * @param color: цвет
   */
  Hill(std::initializer_list<lib::Point> points,
       QColor color = QColor(50, 200, 50, 255))
      : data_(points), color_{color} {}

  Hill(std::vector<lib::Point> points, QColor color = QColor(50, 200, 50, 255))
      : data_(points), color_{color} {}

  Hill(const lib::Hill& data, QColor color = QColor(50, 200, 50, 255))
      : data_(data), color_{color} {}

  Hill(const Hill&) = default;
  Hill(Hill&&) = default;

  Hill& operator=(const Hill&) = default;
  Hill& operator=(Hill&&) = default;

  lib::Point GetCenter() const { return data_.GetCenter(); }
  double GetRadius() const { return data_.GetRadius(); }

  const lib::Hill& GetData() const { return data_; }
  lib::Hill& GetData() { return data_; }

  const std::vector<lib::Point>& GetPoints() const { return data_.GetPoints(); }
  std::vector<lib::Point>& GetPoints() { return data_.GetPoints(); }

  void Draw(QCustomPlot* plot) override;

  /**
   * @brief Возвращает индекс на полотне [plottable]
   * @return size_t: индекс
   */
  size_t GetPlottableIndex() const { return plottable_index_; }

  /**
   * @brief Возвращает значение указателя на полотне
   * @return QCPGraph*: указатель
   */
  QCPCurve* GetCurvePtr() const { return curve_; }

 private:
  lib::Hill data_;
  QColor color_;
  size_t plottable_index_{ULLONG_MAX};
  QCPCurve* curve_{nullptr};
};

}  // namespace gui
