#pragma once

#include "circle_obstacle.h"
namespace math {
double DistanceBetweenPoints(const Point& p1, const Point& p2);

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2);

LinearFunction MakeLinearFunction(const Point& point1, const Point& point2);

// Точки касания прямой к окружснотям
std::pair<Point, Point> CrossPoints(const LinearFunction& tangent,
                                    const CircleObstacle& circle1,
                                    const CircleObstacle& circle2);

std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& crcl,
                                              const Point& point);

std::vector<LinearFunction> TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2);

// Пересекает ли отрезок, проведенный через две точки, окружность
bool AreThereIntersections(const CircleObstacle& crcl, const Point& pnt1,
                           const Point& pnt2);

}  // namespace math
