#pragma once

// our code libs:
#include "base.h"
#include "lib/segment.h"

namespace gui {

/**
 * @brief Фигура отрезка траектории
 * @details Фигура представляет собой отрезок или дугу окружности синего цвета
 */
class Segment : private Drawable {
 public:
  Segment() = default;

  Segment(const lib::Segment& data) : data_{data} {}

  Segment(const lib::Point& start, const lib::Point& end) : data_(start, end) {}

  Segment(const lib::Point& start, const lib::Point& end,
          const lib::Point& center)
      : data_(start, end, center) {}

  double Radius() { return data_.Radius(); }

  /// @brief Возвращает начало сегмента
  lib::Point& Start() { return data_.Start(); }

  /// @brief Возвращает конец сегмента
  lib::Point& End() { return data_.End(); }

  /**
   * @brief Возвращает центр окружности
   * @return Point&: центр окружности
   */
  lib::Point& Center() { return data_.Center(); }

  /**
   * @brief Проверяет, является ли текущий сегмент дугой окружности
   * @return true: да, является
   * @return false: нет, не является
   */
  bool IsArc() { return data_.IsArc(); }

  /**
   * @brief Возвращает угловые коэффициенты на окружности
   * @return std::pair<double, double>: угол первой точки, угол второй точки
   */
  std::pair<double, double> ToAnglesOnCircle() {
    return data_.ToAnglesOnCircle();
  }

  /**
   * @brief Отрисовывает фигуру на полотне
   * @details Фигура представляет собой отрезок или дугу окружности синего цвета
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;

 private:
  lib::Segment data_;

  QColor color_{QColor(50, 100, 200, 255)};
};

}  // namespace gui
