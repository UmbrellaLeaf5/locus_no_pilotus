#pragma once

#include <memory>

#include "point.h"

namespace lib {

/**
 * @brief Математический отрезок траектории
 * @details Может быть как отрезком, так и дугой некоторой окружности
 */
class Segment {
 public:
  Segment(Point start, Point end) : start{start}, end{end} {}

  Segment(Point start, Point end, Point center)
      : start{start}, end{end}, center_ptr{&center} {}

  Point start;

  Point end;

  std::unique_ptr<Point> center_ptr = std::nullptr;
};

}  // namespace lib
