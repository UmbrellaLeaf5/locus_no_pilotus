// header file:
#include "point.h"

// std libs:
#include <stdexcept>

namespace lib {

/**
 * @brief Оператор сравнения двух точек
 * @details Работает как примерно равно (с точностью precision = 1.0E-6)
 * @param a: первая точка
 * @param b: вторая точка
 * @return true: если точки примерно равны
 * @return false: если точки не равны даже примерно
 */
bool operator==(Point a, Point b) {
  return std::abs(a.x - b.x) < precision && std::abs(a.y - b.y) < precision;
}

/**
 * @brief Находит расстояние между двумя мат. точками
 * @param first_point: первая точка
 * @param second_point: вторая точка
 * @return double: искомое расстояние
 */
double DistanceBetweenPoints(const Point& first_point,
                             const Point& second_point) {
  return sqrt(pow(second_point.x - first_point.x, 2) +
              pow(second_point.y - first_point.y, 2));
}

/**
 * @brief Находит, в какой части окружности лежит мат. точка
 * @param point: мат. точка
 * @param center: центр окружности (тоже мат. точка)
 * @return CircleQuadrant: конкретная четверть окружности
 */
CircleQuadrant QuadrantOccupiedByPoint(const lib::Point& point,
                                       const lib::Point& center) {
  auto rad = DistanceBetweenPoints(point, center);
  double cos = (point - center).x / rad, sin = (point - center).y / rad;

  // да, здесь везде стоят нестрогие условия, это корректно
  // таким образом нужный случай попадёт просто в наименьшую четверть

  // I четверть
  if ((cos >= 0 && cos <= 1) /* cos: [0;1] */ &&
      (sin >= 0 && sin <= 1) /* sin: [0;1] */)
    return CircleQuadrant::First;

  // II четверть
  else if ((cos >= -1 && cos <= 0) /* cos: [-1;0] */ &&
           (sin >= 0 && sin <= 1) /*  sin: [0;1] */)
    return CircleQuadrant::Second;

  // III четверть
  else if ((cos >= -1 && cos <= 0) /*  cos: [-1;0] */ &&
           (sin >= -1 && sin <= 0) /*  sin: [-1;0] */)
    return CircleQuadrant::Third;

  // IV четверть
  else if ((cos >= 0 && cos <= 1) /*  cos: [0;1] */ &&
           (sin >= -1 && sin <= 0) /* sin: [-1;0] */)
    return CircleQuadrant::Fourth;

  // impossible case
  return CircleQuadrant::First;
}

/**
 * @brief Инициализирует новый экземпляр Point As Angles:: Point As Angles
 *
 * @param positive_angle
 * @param negative_angle
 */
PointAsAngles::PointAsAngles(double positive_angle, double negative_angle)
    : positive_angle{positive_angle}, negative_angle{negative_angle} {
  if (positive_angle < -lib::precision || negative_angle > lib::precision) {
    throw std::runtime_error("dev: error signed angles in PointAsAngles");
  }
}

/**
 * @brief Переводит мат. точку в мат. точку на ед. окружности
 * @param point: изначальная мат. точка
 * @param center: центр окружности, относительно которого считать
 * @return PointAsAngles: мат. точка на ед. окружности
 */
PointAsAngles PointAsAngles::FromPoint(const lib::Point& point,
                                       const lib::Point& center) {
  auto rad = DistanceBetweenPoints(point, center);
  double cos = (point - center).x / rad, sin = (point - center).y / rad;

  auto quarter = QuadrantOccupiedByPoint(point, center);
  double angle = std::abs(std::atan2(sin, cos) * 180.0 / M_PI);

  switch (quarter) {
    case CircleQuadrant::First:
    case CircleQuadrant::Second: {
      return {angle, angle - 360};
    }
    case CircleQuadrant::Third:
    case CircleQuadrant::Fourth: {
      return {360 - angle, -angle};
    }
  }

  // impossible case
  return InfPoint();
}

}  // namespace lib