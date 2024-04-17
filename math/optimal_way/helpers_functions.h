#pragma once

#include "obstacles.h"

namespace math {

double DistanceBetweenPoints(const Point& p1, const Point& p2);

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2);

/**
 * @brief Находит точки касания кругов с их общей касательной
 * @param tangent: касательная
 * @param circle1: круг 1
 * @param circle2: круг 2
 * @return точки касательной
 */
std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const CircleObstacle& circle1,
                                      const CircleObstacle& circle2);

/**
 * @brief Находит точки касания кругов c касательной,
 * проведенной из контрольной точки
 * @param cr_obst: круг
 * @param point: контрольная точка
 * @return точки касательной
 */
std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& cr_obst,
                                              const Point& point);

/**
 * @brief Находит уравнения общих касательных двух кругов
 * @param circle1: круг 1
 * @param circle2: круг 2
 * @return уравнения касательных
 */
std::vector<LinearFunction> TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2);

/**
 * @brief Проверяет, пересекает ли отрезок,
 * проведенный через две точки, окружность
 * @param cr_obst: круг
 * @param pnt1: точка 1
 * @param pnt2: точка 2
 * @return результат проверки
 */
bool AreThereIntersections(const CircleObstacle& cr_obst, const Point& pnt1,
                           const Point& pnt2);

}  // namespace math
