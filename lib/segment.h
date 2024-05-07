#pragma once

#include <cmath>
#include <memory>
#include <stdexcept>

#include "point.h"

namespace lib {

static double DistanceBetweenPoints(const Point& p1, const Point& p2) {
  return pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 0.5);
}

/**
 * @brief Сегмент математический траектории
 * @details Может быть как отрезком, так и дугой некоторой окружности
 */
class Segment {
 public:
  /**
   * @brief Инициализирует новый экземпляр сегмента,
   * как отрезок с началом и концом
   * @param start: точка начала
   * @param end: точка конца
   */
  Segment(const Point& start, const Point& end) : start{start}, end{end} {}

  /**
   * @brief Инициализирует новый экземпляр сегмента,
   * как дугу окружности с началом и концом
   * @param start: точка начала
   * @param end: точка конца
   * @param center: центр окружности
   */
  Segment(const Point& start, const Point& end, Point center)
      : start{start}, end{end}, center_ptr{&center} {
    if (std::abs(DistanceBetweenPoints(start, center) -
                 DistanceBetweenPoints(end, center)) < lib::precision)
      throw std::logic_error(
          "dev: start and end in Segment do not lie on the same circle");
  }

  /// @brief Возвращает начало сегмента
  Point& Start() { return start; }

  /// @brief Возвращает конец сегмента
  Point& End() { return end; }

  /**
   * @brief Возвращает центр окружности
   * @return Point&: центр окружности
   * @throw std::runtime_error: если сегмент не имеет отношения к окружности
   */
  Point& Center() {
    if (center_ptr) return *center_ptr;

    throw std::runtime_error("dev: center in Segment is nullptr");
  }

  /// @brief Возвращает радиус окружности
  double Radius() { return DistanceBetweenPoints(start, *center_ptr); }

  /**
   * @brief Проверяет, является ли текущий сегмент дугой окружности
   * @return true: да, является
   * @return false: нет, не является
   */
  bool IsArc() { return center_ptr != nullptr; }

 private:
  Point start;
  Point end;
  std::unique_ptr<Point> center_ptr;
};

}  // namespace lib
