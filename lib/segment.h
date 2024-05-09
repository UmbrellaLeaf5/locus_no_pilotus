#pragma once

// our code libs:
#include "point.h"

namespace lib {

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
  Segment(const Point& start, const Point& end) : start_{start}, end_{end} {}

  /**
   * @brief Инициализирует новый экземпляр сегмента,
   * как дугу окружности с началом и концом
   * @param start: точка начала
   * @param end: точка конца
   * @param center: центр окружности
   */
  Segment(const Point& start, const Point& end, const Point& center);

  /// @brief Возвращает начало сегмента
  Point& Start() { return start_; }

  /// @brief Возвращает начало сегмента
  const Point& Start() const { return start_; }

  /// @brief Возвращает конец сегмента
  Point& End() { return end_; }

  /// @brief Возвращает конец сегмента
  const Point& End() const { return end_; }

  /**
   * @brief Возвращает центр окружности
   * @return Point&: центр окружности
   * @throw std::runtime_error: если сегмент не имеет отношения к окружности
   */
  Point& Center();

  /**
   * @brief Возвращает центр окружности
   * @return const Point&: центр окружности
   * @throw std::runtime_error: если сегмент не имеет отношения к окружности
   */
  const Point& Center() const;

  /**
   * @brief Возвращает радиус окружности
   * @return double радиус окружности
   * @throw std::runtime_error: если сегмент не имеет отношения к окружности
   */
  double Radius() const;

  /**
   * @brief Проверяет, является ли текущий сегмент дугой окружности
   * @return true: да, является
   * @return false: нет, не является
   */
  bool IsArc() const { return !isinf(center_); }

  /**
   * @brief Возвращает угловые коэффициенты на окружности
   * @return std::pair<double, double>: угол первой точки, угол второй точки
   */
  std::pair<double, double> ToAnglesOnCircle();

  /**
   * @brief Проверяет, может ли сегмент стать дугой с учетом центра окружности
   * @param seg: сегмент
   * @param center: центр предполагаемой окружности
   * @return true: если может
   * @return false: если выпадет исключение
   */
  static bool CouldBeArc(const lib::Segment& seg, const lib::Point& center);

 private:
  Point start_;
  Point end_;
  Point center_{Point::InfPoint()};
};

}  // namespace lib
