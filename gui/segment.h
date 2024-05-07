#pragma once

#include "base.h"
#include "lib/segment.h"

enum class QuarterOfCircle { First, Second, Third, Fourth };

namespace gui {

/**
 * @brief Фигура отрезка траектории
 * @details Фигура представляет собой отрезок или дугу окружности синего цвета
 */
struct Segment : Drawable {
 public:
  Segment() = default;

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
   * @param Точка старта
   * @param Конечная точка
   * @param Центр окружности
   * @return std::pair<double, double>: угол первой точки, угол второй точки
   */
  static std::pair<double, double> GetAngles(lib::Point start, lib::Point end,
                                             const lib::Point& center);

  /**
   * @brief Отрисовывает фигуру на полотне
   * @details Фигура представляет собой отрезок или дугу окружности синего цвета
   * @param plot: указатель на полотно
   */
  virtual void Draw(QCustomPlot* plot) override;

 private:
  lib::Segment data_;

  static QuarterOfCircle GetQuarterOfCircle(const lib::Point& p);
  static double GetMinAngle(const lib::Point& p, double R,
                            QuarterOfCircle quarter);
};

}  // namespace gui
