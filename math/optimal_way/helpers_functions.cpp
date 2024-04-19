#include "helpers_functions.h"

#include <algorithm>
#include <cmath>

namespace math {

double DistanceBetweenPoints(const Point& p1, const Point& p2) {
  return pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 0.5);
}

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2) {
  double line = DistanceBetweenPoints(p1, p2);
  double cos_alpha = (pow(line, 2) - 2 * pow(circle.GetRadius(), 2)) /
                     (2 * circle.GetRadius());
  return circle.GetRadius() * acos(cos_alpha);
}

double DistanceBetweenPointsOnPolygon(const PolygonObstacle& polygon,
                                      const Point& p1, const Point& p2) {
  if (!AreThereIntersections(polygon, p1, p2))
    return DistanceBetweenPoints(p1, p2);
  std::vector<Point> vertexes = polygon.GetVertexes();
  std::size_t index1 = std::distance(
      vertexes.begin(), std::find(vertexes.begin(), vertexes.end(), p1));
  std::size_t index2 = std::distance(
      vertexes.begin(), std::find(vertexes.begin(), vertexes.end(), p2));
  std::vector<double> distances(vertexes.size());
  for (auto& elem : distances) elem = inf;
  distances[index1] = 0;
  while (index1 != index2) {
    for (std::size_t i = 0; i < distances.size(); ++i)
      if (!AreThereIntersections(polygon, vertexes[index1], vertexes[i], ))
        dist = std::min(distances[i],
                        DistanceBetweenPoints(vertexes[index1], vertexes[i]) +
                            distances[index1]);
    index1 = std::distance(
        distances.begin(),
        std::find(distances.begin(), distances.end(), std::min(distances)));
  }
  return distances[index2];
}

std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const CircleObstacle& circle1,
                                      const CircleObstacle& circle2) {
  double a = tangent.a_coef;
  double b = tangent.b_coef;
  double c = tangent.c_coef;
  double x_0 = circle1.GetCenter().x;
  double y_0 = circle1.GetCenter().y;
  double x_1 = circle2.GetCenter().x;
  double y_1 = circle2.GetCenter().y;
  double point1_x = (-((a / b) * (c / b + y_0) - x_0)) / (1 + pow(a / b, 2));
  double point1_y = a / b * point1_x - c / b;
  double point2_x = (-((a / b) * (c / b + y_1) - x_1)) / (1 + pow(a / b, 2));
  double point2_y = a / b * point2_x - c / b;
  Point point1(point1_x, point1_y);
  Point point2(point2_x, point2_y);
  return std::make_pair(point1, point2);
}

std::pair<Point, Point> TangentPointsToCircle(const CircleObstacle& cr_obst,
                                              const Point& pnt) {
  Point center = cr_obst.GetCenter();
  double radius = cr_obst.GetRadius();
  double discriminant = pow((center.x - pnt.x) * (center.y - pnt.y), 2) -
                        (pow(radius, 2) - pow(pnt.x - center.x, 2)) *
                            (pow(radius, 2) - pow(pnt.y - center.y, 2));
  double slope_1 =
      (-(center.x - pnt.x) * (center.y - pnt.y) + sqrt(discriminant)) /
      (pow(radius, 2) - pow(pnt.x - center.x, 2));
  double slope_2 =
      (-(center.x - pnt.x) * (center.y - pnt.y) - sqrt(discriminant)) /
      (pow(radius, 2) - pow(pnt.x - center.x, 2));
  double b1_coef = pnt.y - slope_1 * pnt.x;
  double b2_coef = pnt.y - slope_2 * pnt.x;
  double x1_tang_pnt = (-(slope_1 * b1_coef - center.x - slope_1 * center.y)) /
                       (1 + pow(slope_1, 2));
  double x2_tang_pnt = (-(slope_2 * b2_coef - center.x - slope_2 * center.y)) /
                       (1 + pow(slope_2, 2));
  double y1_tang_pnt = slope_1 * x1_tang_pnt + b1_coef;
  double y2_tang_pnt = slope_2 * x2_tang_pnt + b2_coef;
  return std::make_pair(Point(x1_tang_pnt, y1_tang_pnt),
                        Point(x2_tang_pnt, y2_tang_pnt));
}

std::pair<Point, Point> TangentPointsToPoly(const PolygonObstacle& poly_obst,
                                            const Point& point) {
  Point center = poly_obst.GetCenter();
  std::vector<Point> vertexes = poly_obst.GetVertexes();
  Point tang_pnt_1 = vertexes[0];
  double cos_alpha_1 = 1;
  Point tang_pnt_2;
  double cos_alpha_2 = 1;
  double dist_to_cnt = DistanceBetweenPoints(center, point);
  LinearFunction line(center, point);
  for (const auto& vertex : vertexes)
    if ((line.a_coef * vertex.x + line.b_coef * vertex.y + line.c_coef) *
            (line.a_coef * vertexes[0].x + line.b_coef * vertexes[0].y +
             line.c_coef) <
        0) {
      tang_pnt_2 = vertex;
      break;
    }
  for (const auto& vertex : vertexes) {
    double dist_to_vrtx = DistanceBetweenPoints(vertex, point);
    double dist_cnt_vrtx = DistanceBetweenPoints(center, vertex);
    double new_cos_alpha =
        (pow(dist_to_vrtx, 2) + pow(dist_to_cnt, 2) - pow(dist_cnt_vrtx, 2)) /
        (2 * dist_to_vrtx * dist_to_cnt);
    if (((line.a_coef * vertex.x + line.b_coef * vertex.y + line.c_coef) *
             (line.a_coef * tang_pnt_1.x + line.b_coef * tang_pnt_1.y +
              line.c_coef) >
         0) &&
        (new_cos_alpha < cos_alpha_1)) {
      tang_pnt_1 = vertex;
      cos_alpha_1 = new_cos_alpha;
    } else if (((line.a_coef * vertex.x + line.b_coef * vertex.y +
                 line.c_coef) *
                    (line.a_coef * tang_pnt_2.x + line.b_coef * tang_pnt_2.y +
                     line.c_coef) >
                0) &&
               (new_cos_alpha < cos_alpha_2)) {
      tang_pnt_2 = vertex;
      cos_alpha_2 = new_cos_alpha;
    }
  }
  return std::make_pair(tang_pnt_1, tang_pnt_2);
}

std::vector<LinearFunction> TangentsBetweenCircles(
    const CircleObstacle& circle1, const CircleObstacle& circle2) {
  std::vector<LinearFunction> tangents;
  double x_1 = circle2.GetCenter().x;
  double y_1 = circle2.GetCenter().y;
  double r_1 = circle2.GetRadius();
  double x_0 = circle1.GetCenter().x;
  double y_0 = circle1.GetCenter().y;
  double r_0 = circle1.GetRadius();

  auto FindTangent = [&x_1, &x_0, &y_1, &y_0](double r_0, double r_1) {
    double b =
        ((r_1 - r_0) * (y_1 - y_0) +
         sqrt(pow(x_1 - x_0, 2) *
              (pow(x_1 - x_0, 2) + pow(y_1 - y_0, 2) - pow(r_1 - r_0, 2)))) /
        (pow(x_1 - x_0, 2) + pow(y_1 - y_0, 2));
    double a = ((r_1 - r_0) - b * (y_1 - y_0)) / (x_1 - x_0);
    double c = r_0 - a * x_0 - b * y_0;
    return LinearFunction(a, b, c);
  };

  for (auto n1 : {-1, 1})
    for (auto n2 : {-1, 1}) tangents.push_back(FindTangent(r_0 * n1, r_1 * n2));
  return tangents;
}

bool AreThereIntersections(const CircleObstacle& cr_obst, const Point& point1,
                           const Point& point2) {
  double slope = (point2.y - point1.y) / (point2.x - point1.x);
  double b_coef = point1.y - slope * point1.x;
  Point center = cr_obst.GetCenter();
  double radius = cr_obst.GetRadius();
  double discriminant = (pow(slope * b_coef - center.x - slope * center.y, 2)) +
                        (pow(radius, 2) - pow(center.x, 2) - pow(b_coef, 2) -
                         pow(center.y, 2) + 2 * b_coef * center.y) *
                            (1 + pow(slope, 2));
  if (discriminant <= 0)
    return false;
  else {
    double x_1 =
        (-(slope * b_coef - center.x - slope * center.y) + sqrt(discriminant)) /
        (1 + pow(slope, 2));
    double x_2 =
        (-(slope * b_coef - center.x - slope * center.y) - sqrt(discriminant)) /
        (1 + pow(slope, 2));
    if ((std::min(point1.x, point2.x) <= x_1 <= std::max(point1.x, point2.x)) ||
        (std::min(point1.x, point2.x) <= x_2 <= std::max(point1.x, point2.x)))
      return true;
    else
      return false;
  }
}

bool AreThereIntersections(const PolygonObstacle& poly_obst, const Point& pnt1,
                           const Point& pnt2) {
  LinearFunction line(pnt1, pnt2);
  std::vector<Point> vertexes = poly_obst.GetVertexes();
  for (std::size_t i = 0; i < vertexes.size() - 1; ++i)
    if ((line.a_coef * vertexes[i].x + line.b_coef * vertexes[i].y +
         line.c_coef) *
            (line.a_coef * vertexes[i + 1].x + line.b_coef * vertexes[i + 1].y +
             line.c_coef) <
        0)
      return true;
  return false;
}

}  // namespace math
