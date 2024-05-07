#include "optimal_way.h"

#include "helpers_functions.h"

namespace math {

template <typename T, typename U>
bool OptimalWayCalculator::TangentGoesTroughOtherObstacle(
    const LinearFunction& tangent, T& obstacle1, U& obstacle2) {
  std::pair<Point, Point> tangent_points =
      TangentPoints(tangent, obstacle1, obstacle2);
  for (std::size_t i = 0; i < circles_.size(); ++i)
    if (AreThereIntersections(circles_[i], tangent_points.first,
                              tangent_points.second))
      return true;
  for (std::size_t i = 0; i < polys_.size(); ++i)
    if (AreThereIntersections(polys_[i], tangent_points.first,
                              tangent_points.second))
      return true;
  return false;
}

template <typename T, typename U>
void OptimalWayCalculator::AddTangent(const LinearFunction& tangent,
                                      T& obstacle1, U& obstacle2) {
  std::pair<Point, Point> tangent_points =
      TangentPoints(tangent, obstacle1, obstacle2);
  tangent_points.first.another_tangent_point =
      std::make_shared<Point>(tangent_points.second);
  tangent_points.second.another_tangent_point =
      std::make_shared<Point>(tangent_points.first);
  obstacle1.AddTangentLine(tangent);
  obstacle1.AddTangentPoint(tangent_points.first);
  obstacle2.AddTangentLine(tangent);
  obstacle2.AddTangentPoint(tangent_points.second);
}

void OptimalWayCalculator::AddCommonTangents() {
  for (std::size_t i = 0; i < circles_.size(); ++i) {
    for (std::size_t j = i + 1; j < circles_.size(); ++j) {
      std::vector<LinearFunction> tangents =
          TangentsBetween(circles_[i], circles_[j]);

      for (std::size_t k = 0; k < tangents.size(); ++k)
        if (!TangentGoesTroughOtherObstacle<CircleObstacle, CircleObstacle>(
                tangents[k], circles_[i], circles_[j]))
          AddTangent<CircleObstacle, CircleObstacle>(tangents[k], circles_[i],
                                                     circles_[j]);
    }
  }
  for (std::size_t i = 0; i < polys_.size(); ++i) {
    for (std::size_t j = 0; j < circles_.size(); ++j) {
      std::vector<LinearFunction> tangents =
          TangentsBetween(polys_[i], circles_[j]);

      for (std::size_t k = 0; k < tangents.size(); ++k)
        if (!TangentGoesTroughOtherObstacle<PolygonObstacle, CircleObstacle>(
                tangents[k], polys_[i], circles_[j]))
          AddTangent<PolygonObstacle, CircleObstacle>(tangents[k], polys_[i],
                                                      circles_[j]);
    }
    for (std::size_t j = i + 1; j < polys_.size(); ++j) {
      std::vector<LinearFunction> tangents =
          TangentsBetween(polys_[i], polys_[j]);

      for (std::size_t k = 0; k < tangents.size(); ++k)
        if (!TangentGoesTroughOtherObstacle<PolygonObstacle, PolygonObstacle>(
                tangents[k], polys_[i], polys_[j]))
          AddTangent<PolygonObstacle, PolygonObstacle>(tangents[k], polys_[i],
                                                       polys_[j]);
    }
  }
}

void OptimalWayCalculator::AddGraphTangentPoints() {
  for (auto& circle : circles_)
    for (auto& point : circle.GetTangentPoints()) {
      PathWayNode new_node(point, graph_.nodes.size());
      new_node.circle_ptr = std::make_unique<CircleObstacle>(circle);
      for (auto& prev : graph_.nodes) {
        if (prev->circle_ptr && ((*prev->circle_ptr) == circle)) {
          graph_.AddEdge(prev->number, new_node.number,
                         DistanceBetweenPointsOnCircle(circle, prev->point,
                                                       new_node.point));
        } else if (prev->circle_ptr &&
                   (new_node.point == (*prev->point.another_tangent_point))) {
          graph_.AddEdge(prev->number, new_node.number,
                         DistanceBetweenPoints(prev->point, new_node.point));
        }
      }
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
    }

  for (auto& poly : polys_)
    for (auto& point : poly.GetTangentPoints()) {
      PathWayNode new_node(point, graph_.nodes.size());
      new_node.poly_ptr = std::make_unique<PolygonObstacle>(poly);
      for (auto& prev : graph_.nodes) {
        if (prev->poly_ptr && ((*prev->poly_ptr) == poly)) {
          graph_.AddEdge((*prev).number, new_node.number,
                         DistanceBetweenPointsOnPolygon(poly, prev->point,
                                                        new_node.point));
        } else if (prev->poly_ptr &&
                   (new_node.point == (*prev->point.another_tangent_point))) {
          graph_.AddEdge((*prev).number, new_node.number,
                         DistanceBetweenPoints(prev->point, new_node.point));
        }
      }
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
    }
}

void OptimalWayCalculator::AddGraphControlPoints(Point point1, Point point2) {
  for (auto& point : {point1, point2}) {
    PathWayNode new_node{point, graph_.nodes.size()};
    for (auto& prev : graph_.nodes) {
      if (prev->circle_ptr) {
        std::pair<Point, Point> tangent_points =
            TangentPoints((*prev->circle_ptr), point);
        for (auto& tangent_point :
             {tangent_points.first, tangent_points.second})
          if (tangent_point == prev->point) {
            bool is_valid = true;
            for (auto& circle : circles_)
              if (AreThereIntersections(circle, prev->point, new_node.point))
                is_valid = false;
            for (auto& poly : polys_)
              if (AreThereIntersections(poly, prev->point, new_node.point))
                is_valid = false;
            if (is_valid)
              graph_.AddEdge(
                  prev->number, new_node.number,
                  DistanceBetweenPoints(prev->point, new_node.point));
          }
      }
      if (prev->poly_ptr) {
        std::pair<Point, Point> tangent_points =
            TangentPoints((*prev->poly_ptr), point);
        for (auto& tangent_point :
             {tangent_points.first, tangent_points.second})
          if (tangent_point == prev->point) {
            bool is_valid = true;
            for (auto& circle : circles_)
              if (AreThereIntersections(circle, prev->point, new_node.point))
                is_valid = false;
            for (auto& poly : polys_)
              if (AreThereIntersections(poly, prev->point, new_node.point))
                is_valid = false;
            if (is_valid)
              graph_.AddEdge(
                  prev->number, new_node.number,
                  DistanceBetweenPoints(prev->point, new_node.point));
          }
      }
    }
    graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
  }
}

std::vector<size_t> OptimalWayCalculator::FindOptimalWay(Point p1, Point p2) {
  AddGraphControlPoints(p1, p2);
  DijkstrasAlgorithm da(graph_);
  return da.Get_Min_Path();
}

template bool OptimalWayCalculator::TangentGoesTroughOtherObstacle<
    CircleObstacle, CircleObstacle>(const LinearFunction& tangent,
                                    CircleObstacle& obstacle1,
                                    CircleObstacle& obstacle2);
template bool OptimalWayCalculator::TangentGoesTroughOtherObstacle<
    PolygonObstacle, CircleObstacle>(const LinearFunction& tangent,
                                     PolygonObstacle& obstacle1,
                                     CircleObstacle& obstacle2);
template bool OptimalWayCalculator::TangentGoesTroughOtherObstacle<
    PolygonObstacle, PolygonObstacle>(const LinearFunction& tangent,
                                      PolygonObstacle& obstacle1,
                                      PolygonObstacle& obstacle2);

template void OptimalWayCalculator::AddTangent<CircleObstacle, CircleObstacle>(
    const LinearFunction& tangent, CircleObstacle& obstacle1,
    CircleObstacle& obstacle2);
template void OptimalWayCalculator::AddTangent<PolygonObstacle, CircleObstacle>(
    const LinearFunction& tangent, PolygonObstacle& obstacle1,
    CircleObstacle& obstacle2);
template void
OptimalWayCalculator::AddTangent<PolygonObstacle, PolygonObstacle>(
    const LinearFunction& tangent, PolygonObstacle& obstacle1,
    PolygonObstacle& obstacle2);
}  // namespace math
