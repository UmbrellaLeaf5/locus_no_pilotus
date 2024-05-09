#include "optimal_way.h"

#include "helpers_functions.h"

namespace math {

template <typename T, typename U>
bool OptimalWayCalculator::TangentGoesThroughOtherObstacle(
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

bool OptimalWayCalculator::TangentGoesThroughOtherObstacle(
    const Point& tangent_point, const Point& control_point) {
  for (auto& circle : circles_)
    if (AreThereIntersections(circle, tangent_point, control_point))
      return true;
  for (auto& poly : polys_)
    if (AreThereIntersections(poly, tangent_point, control_point)) return true;
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
        if (!TangentGoesThroughOtherObstacle<CircleObstacle, CircleObstacle>(
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
        if (!TangentGoesThroughOtherObstacle<PolygonObstacle, CircleObstacle>(
                tangents[k], polys_[i], circles_[j]))
          AddTangent<PolygonObstacle, CircleObstacle>(tangents[k], polys_[i],
                                                      circles_[j]);
    }
    for (std::size_t j = i + 1; j < polys_.size(); ++j) {
      std::vector<LinearFunction> tangents =
          TangentsBetween(polys_[i], polys_[j]);

      for (std::size_t k = 0; k < tangents.size(); ++k)
        if (!TangentGoesThroughOtherObstacle<PolygonObstacle, PolygonObstacle>(
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
      new_node.circle_ptr = std::make_shared<CircleObstacle>(circle);
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
      for (std::size_t i = 0; i < graph_.nodes.size() - 1; ++i) {
        if (graph_.nodes[i]->circle_ptr &&
            ((*graph_.nodes[i]->circle_ptr) == circle)) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node.number,
                         DistanceBetweenPointsOnCircle(
                             circle, graph_.nodes[i]->point, new_node.point));
        } else if (new_node.point ==
                   *graph_.nodes[i]->point.another_tangent_point) {
          graph_.AddEdge(
              graph_.nodes[i]->number, new_node.number,
              DistanceBetweenPoints(graph_.nodes[i]->point, new_node.point));
        }
      }
    }

  for (auto& poly : polys_)
    for (auto& point : poly.GetTangentPoints()) {
      PathWayNode new_node(point, graph_.nodes.size());
      new_node.poly_ptr = std::make_unique<PolygonObstacle>(poly);
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
      for (std::size_t i = 0; i < graph_.nodes.size() - 1; ++i) {
        if (graph_.nodes[i]->poly_ptr &&
            ((*graph_.nodes[i]->poly_ptr) == poly)) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node.number,
                         DistanceBetweenPointsOnPolygon(
                             poly, graph_.nodes[i]->point, new_node.point));
        } else if (new_node.point ==
                   *graph_.nodes[i]->point.another_tangent_point) {
          graph_.AddEdge(
              graph_.nodes[i]->number, new_node.number,
              DistanceBetweenPoints(graph_.nodes[i]->point, new_node.point));
        }
      }
    }
}

std::size_t OptimalWayCalculator::AddGraphControlPoints(Point point) {
  for (auto& circle : circles_) {
    std::pair<Point, Point> tangent_points = TangentPoints(circle, point);
    for (auto& tangent_point : {tangent_points.first, tangent_points.second}) {
      if (TangentGoesThroughOtherObstacle(tangent_point, point)) continue;
      PathWayNode new_node(tangent_point, graph_.nodes.size());
      new_node.circle_ptr = std::make_shared<CircleObstacle>(circle);
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
      for (std::size_t i = 0; i < graph_.nodes.size() - 1; ++i) {
        if (*graph_.nodes[i]->circle_ptr == circle) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node.number,
                         DistanceBetweenPointsOnCircle(circle, tangent_point,
                                                       graph_.nodes[i]->point));
        }
      }
    }
  }
  for (auto& poly : polys_) {
    std::pair<Point, Point> tangent_points = TangentPoints(poly, point);
    for (auto& tangent_point : {tangent_points.first, tangent_points.second}) {
      if (TangentGoesThroughOtherObstacle(tangent_point, point)) continue;
      PathWayNode new_node(tangent_point, graph_.nodes.size());
      new_node.poly_ptr = std::make_shared<PolygonObstacle>(poly);
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
      for (std::size_t i = 0; i < graph_.nodes.size() - 1; ++i) {
        if (*graph_.nodes[i]->poly_ptr == poly) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node.number,
                         DistanceBetweenPointsOnPolygon(
                             poly, tangent_point, graph_.nodes[i]->point));
        }
      }
    }
  }
  return graph_.nodes.size();
}

void OptimalWayCalculator::FindOptimalWay(Point p1, Point p2) {
  std::size_t point1_new_nodes = AddGraphControlPoints(p1);
  std::size_t point2_new_nodes = AddGraphControlPoints(p2);
  PathWayNode new_node1(p1, graph_.nodes.size());
  graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node1));
  for (std::size_t i = normal_graph_size_; i < point1_new_nodes; ++i)
    graph_.AddEdge(graph_.nodes[i]->number, new_node1.number,
                   DistanceBetweenPoints(graph_.nodes[i]->point, p1));
  PathWayNode new_node2(p2, graph_.nodes.size());
  graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node2));
  for (std::size_t i = point1_new_nodes; i < point2_new_nodes; ++i)
    graph_.AddEdge(graph_.nodes[i]->number, new_node2.number,
                   DistanceBetweenPoints(graph_.nodes[i]->point, p2));
  if (!TangentGoesThroughOtherObstacle(p1, p2))
    graph_.AddEdge(graph_.nodes.size() - 2, graph_.nodes.size() - 1,
                   DistanceBetweenPoints(p1, p2));
  // std::cout << normal_graph_size_ << std::endl;
  // for (auto& elem : graph_.nodes) {
  //   std::cout << "Point" << elem->number << ":" << std::endl;
  //   std::cout << elem->point.x << " " << elem->point.y << std::endl;
  //   std::cout << "Point`s edges:" << std::endl;
  //   for (auto& elem1 : elem->edges) {
  //     std::cout << "Point" << elem1->number << " " << elem1->point.x << " "
  //               << elem1->point.y << std::endl;
  //   }
  //   std::cout << "\n" << std::endl;
  // }

  DijkstrasAlgorithm da(graph_);
  optimal_way_ = da.Get_Min_Path();
  optimal_way_length_ = da.Get_Min_Len();
  graph_.RemoveLastNodes(graph_.nodes.size() - normal_graph_size_);
}

template bool OptimalWayCalculator::TangentGoesThroughOtherObstacle<
    CircleObstacle, CircleObstacle>(const LinearFunction& tangent,
                                    CircleObstacle& obstacle1,
                                    CircleObstacle& obstacle2);
template bool OptimalWayCalculator::TangentGoesThroughOtherObstacle<
    PolygonObstacle, CircleObstacle>(const LinearFunction& tangent,
                                     PolygonObstacle& obstacle1,
                                     CircleObstacle& obstacle2);
template bool OptimalWayCalculator::TangentGoesThroughOtherObstacle<
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
