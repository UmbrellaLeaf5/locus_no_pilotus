#include "helpers_functions.h"

#include <algorithm>
#include <cmath>

namespace math {

double DistanceBetweenPoints(const Point& p1, const Point& p2) {
  return pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 0.5);
}

double DistanceBetweenPointsOnCircle(const CircleObstacle& circle,
                                     const Point& p1, const Point& p2) {
  if (p1 == p2) return 0;
  double line = DistanceBetweenPoints(p1, p2);
  double cos_alpha = (2 * pow(circle.GetRadius(), 2) - pow(line, 2)) /
                     (2 * pow(circle.GetRadius(), 2));
  return std::abs(cos_alpha) < 1 ? circle.GetRadius() * acos(cos_alpha)
                                 : circle.GetRadius() * M_PI;
}

double DistanceBetweenPointsOnPolygon(const PolygonObstacle& polygon,
                                      const Point& p1, const Point& p2) {
  std::vector<Point> vertexes = polygon.GetVertexes();
  std::size_t index1 = std::distance(
      vertexes.begin(), std::find(vertexes.begin(), vertexes.end(), p1));
  std::size_t index2 = std::distance(
      vertexes.begin(), std::find(vertexes.begin(), vertexes.end(), p2));
  std::size_t iter = index1;
  double d1 = 0;
  while (iter != index2) {
    d1 += DistanceBetweenPoints(vertexes[iter],
                                vertexes[(iter + 1) % vertexes.size()]);
    iter = (iter + 1) % vertexes.size();
  }

  double d2 = 0;
  while (iter != index1) {
    d2 += DistanceBetweenPoints(vertexes[iter],
                                vertexes[(iter + 1) % vertexes.size()]);
    iter = (iter + 1) % vertexes.size();
  }
  return std::min(d1, d2);
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
  double point1_x =
      (-(a * (c + y_0 * b) - x_0 * pow(b, 2))) / (pow(a, 2) + pow(b, 2));
  double point2_x =
      (-(a * (c + y_1 * b) - x_1 * pow(b, 2))) / (pow(a, 2) + pow(b, 2));
  double point1_y, point2_y;
  if (b) {
    point1_y = a / b * point1_x - c / b;
    point2_y = a / b * point2_x - c / b;
  } else {
    point1_y = y_0;
    point2_y = y_1;
  }
  Point point1(point1_x, point1_y);
  Point point2(point2_x, point2_y);
  return std::make_pair(point1, point2);
}

std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const PolygonObstacle& polygon1,
                                      const PolygonObstacle& polygon2) {
  std::pair<Point, Point> tang_pnts;
  std::vector<Point> vertexes1 = polygon1.GetVertexes();
  for (auto& vertex : vertexes1)
    if (std::abs(tangent.a_coef * vertex.x + tangent.b_coef * vertex.y +
                 tangent.c_coef) <= precision)
      tang_pnts.first = vertex;

  std::vector<Point> vertexes2 = polygon2.GetVertexes();
  for (auto& vertex : vertexes2)
    if (std::abs(tangent.a_coef * vertex.x + tangent.b_coef * vertex.y +
                 tangent.c_coef) <= precision)
      tang_pnts.second = vertex;
  return tang_pnts;
}

std::pair<Point, Point> TangentPoints(const LinearFunction& tangent,
                                      const PolygonObstacle& polygon,
                                      const CircleObstacle& circle) {
  std::pair<Point, Point> tang_pnts;
  std::vector<Point> vertexes = polygon.GetVertexes();
  for (auto& vertex : vertexes)
    if (std::abs(tangent.a_coef * vertex.x + tangent.b_coef * vertex.y +
                 tangent.c_coef) <= precision)
      tang_pnts.first = vertex;

  std::pair<Point, Point> cr_points = TangentPoints(circle, tang_pnts.first);
  for (auto& point : {cr_points.first, cr_points.second})
    if (std::abs(tangent.a_coef * point.x + tangent.b_coef * point.y +
                 tangent.c_coef) <= precision)
      tang_pnts.second = point;
  return tang_pnts;
}

std::pair<Point, Point> TangentPoints(const CircleObstacle& cr_obst,
                                      const Point& point) {
  Point center = cr_obst.GetCenter();
  double radius = cr_obst.GetRadius();
  double dist = DistanceBetweenPoints(center, point);
  double theta = acos(radius / dist);
  double delta = atan2(point.y - center.y, point.x - center.x);
  double delta1 = delta + theta;
  double delta2 = delta - theta;
  double x1_tang_pnt = center.x + radius * cos(delta1);
  double x2_tang_pnt = center.x + radius * cos(delta2);
  double y1_tang_pnt = center.y + radius * sin(delta1);
  double y2_tang_pnt = center.y + radius * sin(delta2);
  return std::make_pair(Point(x1_tang_pnt, y1_tang_pnt),
                        Point(x2_tang_pnt, y2_tang_pnt));
}

std::pair<Point, Point> TangentPoints(const PolygonObstacle& poly_obst,
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
    if ((line.Substitute(vertex) * line.Substitute(tang_pnt_1) > 0) &&
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

std::vector<LinearFunction> TangentsBetween(const CircleObstacle& circle1,
                                            const CircleObstacle& circle2) {
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
    for (auto n2 : {-1, 1}) {
      tangents.push_back(FindTangent(r_0 * n1, r_1 * n2));
      for (std::size_t i = 0; i < tangents.size() - 1; ++i)
        if (tangents[i] == FindTangent(r_0 * n1, r_1 * n2)) tangents.pop_back();
    }
  return tangents;
}

template <typename T>
std::vector<LinearFunction> TangentsBetween(const PolygonObstacle& polygon,
                                            const T& obstacle) {
  std::vector<LinearFunction> tangents;
  std::vector<Point> vertexes = polygon.GetVertexes();
  for (auto& vertex : vertexes) {
    std::pair<Point, Point> tang_pnts = TangentPoints(obstacle, vertex);
    if (!AreThereIntersections(polygon, vertex, tang_pnts.first))
      tangents.push_back(LinearFunction(vertex, tang_pnts.first));
    if (!AreThereIntersections(polygon, vertex, tang_pnts.second))
      tangents.push_back(LinearFunction(vertex, tang_pnts.second));
  }
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
  for (std::size_t i = 0; i < vertexes.size() - 1; ++i) {
    LinearFunction v_line(vertexes[i], vertexes[i + 1]);
    if ((line.Substitute(vertexes[i]) * line.Substitute(vertexes[i + 1]) < 0) &&
        (v_line.Substitute(pnt1) * v_line.Substitute(pnt2) < 0))
      return true;
  }
  std::size_t prev = -1;
  for (std::size_t i = 0; i < vertexes.size(); ++i)
    if (std::abs(line.Substitute(vertexes[i])) <= precision)
      if (prev == -1)
        prev = i;
      else if (i - prev > 1)
        return true;
  return false;
}

template std::vector<LinearFunction> TangentsBetween<CircleObstacle>(
    const PolygonObstacle& polygon, const CircleObstacle& obstacle);
template std::vector<LinearFunction> TangentsBetween<PolygonObstacle>(
    const PolygonObstacle& polygon, const PolygonObstacle& obstacle);

}  // namespace math
