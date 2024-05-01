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

  const lib::Hill& GetData() const { return data_; }
  lib::Hill& GetData() { return data_; }

  const std::vector<lib::Point>& GetPoints() const { return data_.GetPoints(); }
  std::vector<lib::Point>& GetPoints() { return data_.GetPoints(); }

  void AddVertice(lib::Point vertice) { data_.AddVertice(vertice); }

  void Draw(QCustomPlot* plot) override;

  /**
   * @brief Возвращает значение указателя на полотне
   * @return QCPGraph*: указатель
   */
  QCPCurve* GetCurvePtr() const { return curve_; }

  bool operator==(const gui::Hill& hill) const {
    return data_ == hill.GetData();
  }

 private:
  lib::Hill data_;
  QColor color_;

  QCPCurve* curve_{nullptr};
};

}  // namespace gui
