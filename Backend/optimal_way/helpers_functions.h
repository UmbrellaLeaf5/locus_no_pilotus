#pragma once

#include "circleobstacle.h"
namespace math {
double DistanceBetweenPoints(const Point& p1, const Point p2);

LinearАunction MakeLinearАunction(const Point& point1, const Point& point2);

// Точки касания прямой к окружснотям
std::pair<Point, Point> CrossPoints(const LinearАunction& tangent,
                                    const CircleObstacle& circle1,
                                    const CircleObstacle& circle2);

std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& crcl,
                                              const Point& point);

std::vector<LinearАunction> TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2);

// Пересекает ли отрезок, проведенный через две точки, окружность
bool AreThereIntersections(const CircleObstacle& crcl, const Point& pnt1,
                           const Point& pnt2);

}  // namespace math