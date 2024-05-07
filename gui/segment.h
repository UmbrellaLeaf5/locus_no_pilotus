#pragma once

#include "base.h"
#include "lib/segment.h"

namespace gui {

/// @brief Фигура отрезка траектории
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

  virtual void Draw(QCustomPlot* plot) override;

 private:
  lib::Segment data_;
};

}  // namespace gui