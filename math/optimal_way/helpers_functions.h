#pragma once

#include "obstacles.h"

namespace math {

double DistanceBetweenPoints(const Point& p1, const Point& p2);

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2);

double DistanceBetweenPointsOnPolygon(const PolygonObstacle& polygon,
                                      const Point& p1, const Point& p2);

/**
 * @brief Находит точки касания кругов с их общей касательной
 * @param tangent: касательная
 * @param circle1: круг 1
 * @param circle2: круг 2
 * @return std::pair<Point, Point>: точки касательной
 */
std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const CircleObstacle& circle1,
                                      const CircleObstacle& circle2);

/**
 * @brief Находит точки касания двух многоугольников с их общей
 * касательной
 * @param tangent: касательная
 * @param polygon1: многоугольник 1
 * @param polygon2: многоугольник 2
 * @return std::pair<Point, Point>: точки касательной
 */
std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const PolygonObstacle& polygon1,
                                      const PolygonObstacle& polygon2);

/**
 * @brief Находит точки касания многоугольника и круга с их общей
 * касательной
 * @param tangent: касательная
 * @param polygon: многоугольник
 * @param circle: круг
 * @return std::pair<Point, Point>: точки касательной
 */
std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const PolygonObstacle& polygon,
                                      const CircleObstacle& circle);

/**
 * @brief Находит точки касания круга c касательной,
 * проведенной из контрольной точки
 * @param cr_obst: круг
 * @param point: контрольная точка
 * @return std::pair<Point, Point>: точки касательной
 */
std::pair<Point, Point> TangentPoints(const CircleObstacle& cr_obst,
                                      const Point& point);

/**
 * @brief Находит точки касания многоугольника c касательной,
 * проведенной из контрольной точки
 * @param poly_obst: многоугольник
 * @param point: контрольная точка
 * @return std::pair<Point, Point>: точки касательной
 */
std::pair<Point, Point> TangentPoints(const PolygonObstacle& poly_obst,
                                      const Point& point);

/**
 * @brief Находит уравнения общих касательных двух кругов
 * @param circle1: круг 1
 * @param circle2: круг 2
 * @return std::vector<LinearFunction>: уравнения касательных
 */
std::vector<LinearFunction> TangentsBetween(const CircleObstacle& circle1,
                                            const CircleObstacle& circle2);

/**
 * @brief Находит уравнения общих касательных многоугольника и другого
 * препятствия
 * @param polygon: многоугольник
 * @param obstacle: препятствие
 * @return уравнения касательных
 */
template <typename T>
std::vector<LinearFunction> TangentsBetween(const PolygonObstacle& polygon,
                                            const T& obstacle);

/**
 * @brief Проверяет, пересекает ли отрезок,
 * проведенный через две точки, окружность
 * @param cr_obst: круг
 * @param pnt1: точка 1
 * @param pnt2: точка 2
 * @return bool: результат проверки
 */
bool AreThereIntersections(const CircleObstacle& cr_obst, const Point& pnt1,
                           const Point& pnt2);

/**
 * @brief Проверяет, пересекает ли прямая многоугольник
 * @param cr_obst: круг
 * @param line: прямая
 * @return bool: результат проверки
 */
bool AreThereIntersections(const CircleObstacle& cr_obst,
                           const LinearFunction& line);

/**
 * @brief Проверяет, пересекает ли отрезок,
 * проведенный через две точки, многоугольник
 * @param poly_obst: многоугольник
 * @param pnt1: точка 1
 * @param pnt2: точка 2
 * @return bool: результат проверки
 */
bool AreThereIntersections(const PolygonObstacle& poly_obst, const Point& pnt1,
                           const Point& pnt2);

/**
 * @brief Проверяет, пересекает ли прямая многоугольник
 * @param poly_obst: многоугольник
 * @param line: прямая
 * @return bool: результат проверки
 */
bool AreThereIntersections(const PolygonObstacle& poly_obst,
                           const LinearFunction& line);

}  // namespace math
