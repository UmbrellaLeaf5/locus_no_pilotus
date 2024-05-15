// header file:
#include "optimal_way.h"

// our code libs:
#include "helpers_functions.h"

using lib::Segment;

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
  obstacle1.AddTangentPoint(tangent_points.first);
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
      bool is_unique = true;
      for (std::size_t i = 0; i < graph_.nodes.size(); ++i) {
        if (point == graph_.nodes[i]->point) {
          is_unique = false;
          break;
        }
      }
      if (is_unique == false) continue;
      PathWayNode* new_node = new PathWayNode(point, graph_.nodes.size(), true);
      new_node->circle_ptr = std::make_shared<CircleObstacle>(circle);
      graph_.AddNode(new_node);
      for (std::size_t i = 0; i < graph_.nodes.size() - 1; ++i) {
        if (graph_.nodes[i]->circle_ptr &&
            ((*graph_.nodes[i]->circle_ptr) == circle)) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node->number,
                         DistanceBetweenPointsOnCircle(
                             circle, graph_.nodes[i]->point, new_node->point));
        } else if (new_node->point ==
                   *graph_.nodes[i]->point.another_tangent_point) {
          graph_.AddEdge(
              graph_.nodes[i]->number, new_node->number,
              DistanceBetweenPoints(graph_.nodes[i]->point, new_node->point));
        }
      }
    }
  for (auto& poly : polys_) {
    std::vector<Point> vertexes = poly.GetVertexes();
    for (std::size_t i = 0; i < vertexes.size(); ++i) {
      PathWayNode* new_node =
          new PathWayNode(vertexes[i], graph_.nodes.size(), true);
      for (std::size_t j = 0; j < poly.GetTangentPoints().size(); ++j) {
        if (poly.GetTangentPoints()[j] == vertexes[i])
          new_node->point = poly.GetTangentPoints()[j];
      }
      new_node->poly_ptr = std::make_shared<PolygonObstacle>(poly);
      graph_.AddNode(new_node);
      // Проводим ребра в графе только между соседними вершинами
      // многоугольника
      if (i != 0)
        graph_.AddEdge(
            graph_.nodes[graph_.nodes.size() - 2]->number, new_node->number,
            DistanceBetweenPoints(graph_.nodes[graph_.nodes.size() - 2]->point,
                                  new_node->point));
      if (i == vertexes.size() - 1)
        graph_.AddEdge(
            graph_.nodes[graph_.nodes.size() - vertexes.size()]->number,
            new_node->number,
            DistanceBetweenPoints(
                graph_.nodes[graph_.nodes.size() - vertexes.size()]->point,
                new_node->point));
      for (auto& tangent_point : poly.GetTangentPoints()) {
        if (tangent_point != new_node->point) continue;
        for (auto& node : graph_.nodes) {
          if (*tangent_point.another_tangent_point != node->point) continue;
          graph_.AddEdge(node->number, new_node->number,
                         DistanceBetweenPoints(node->point, new_node->point));
        }
      }
    }
  }
}

std::set<std::size_t> OptimalWayCalculator::AddGraphControlPoints(Point point) {
  std::set<std::size_t> tangent_points_numbers;
  for (auto& circle : circles_) {
    std::pair<Point, Point> tangent_points = TangentPoints(circle, point);
    for (auto& tangent_point : {tangent_points.first, tangent_points.second}) {
      if (TangentGoesThroughOtherObstacle(tangent_point, point)) continue;
      bool is_unique = true;
      for (std::size_t i = 0; i < graph_.nodes.size(); ++i) {
        if (tangent_point == graph_.nodes[i]->point) {
          is_unique = false;
          tangent_points_numbers.insert(graph_.nodes[i]->number);
          break;
        }
      }
      if (!is_unique) continue;
      PathWayNode* new_node =
          new PathWayNode(tangent_point, graph_.nodes.size(), false);
      new_node->circle_ptr = std::make_shared<CircleObstacle>(circle);
      tangent_points_numbers.insert(graph_.nodes.size());
      graph_.AddNode(new_node);

      for (std::size_t i = 0; i < graph_.nodes.size(); ++i) {
        if ((graph_.nodes[i]->circle_ptr) &&
            (*graph_.nodes[i]->circle_ptr == circle) &&
            (graph_.nodes[i]->number != new_node->number)) {
          graph_.AddEdge(graph_.nodes[i]->number, new_node->number,
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
      for (std::size_t i = 0; i < graph_.nodes.size(); ++i) {
        if (tangent_point == graph_.nodes[i]->point) {
          tangent_points_numbers.insert(graph_.nodes[i]->number);
          break;
        }
      }
    }
  }

  return tangent_points_numbers;
}

void OptimalWayCalculator::FindOptimalWay(Point p1, Point p2) {
  ResetInformation();
  std::set<std::size_t> point1_tangents = AddGraphControlPoints(p1);
  std::set<std::size_t> point2_tangents = AddGraphControlPoints(p2);

  PathWayNode* new_node1 = new PathWayNode(p1, graph_.nodes.size(), false);
  graph_.AddNode(new_node1);
  for (const auto& index : point1_tangents) {
    graph_.AddEdge(
        new_node1->number, graph_.nodes[index]->number,
        DistanceBetweenPoints(new_node1->point, graph_.nodes[index]->point));
  }
  PathWayNode* new_node2 = new PathWayNode(p2, graph_.nodes.size(), false);
  graph_.AddNode(new_node2);
  for (const auto& index : point2_tangents) {
    graph_.AddEdge(
        new_node2->number, graph_.nodes[index]->number,
        DistanceBetweenPoints(new_node2->point, graph_.nodes[index]->point));
  }

  if (!TangentGoesThroughOtherObstacle(p1, p2)) {
    graph_.AddEdge(graph_.nodes.size() - 2, graph_.nodes.size() - 1,
                   DistanceBetweenPoints(p1, p2));
  }

  DijkstrasAlgorithm da(graph_);
  optimal_way_ = da.Get_Min_Path();
  optimal_way_length_ = da.Get_Min_Len();
  MakeTrajectoryPart();
  graph_.RemoveNonConstantNodes();
}

void OptimalWayCalculator::MakeTrajectoryPart() {
  for (std::size_t i = 0; i < optimal_way_.size() - 1; ++i) {
    // Если точки лежат на одной окружности, их следует соединить дугой
    if ((graph_.nodes[optimal_way_[i]]->circle_ptr) &&
        (graph_.nodes[optimal_way_[i + 1]]->circle_ptr) &&
        (*(graph_.nodes[optimal_way_[i]]->circle_ptr) ==
         *(graph_.nodes[optimal_way_[i + 1]]->circle_ptr))) {
      trajectory_part_.push_back(
          Segment(graph_.nodes[optimal_way_[i]]->point,
                  graph_.nodes[optimal_way_[i + 1]]->point,
                  graph_.nodes[optimal_way_[i]]->circle_ptr->GetCenter()));
    } else {
      trajectory_part_.push_back(
          Segment(graph_.nodes[optimal_way_[i]]->point,
                  graph_.nodes[optimal_way_[i + 1]]->point));
    }
  }
}

void OptimalWayCalculator::ResetInformation() {
  trajectory_part_.clear();
  for (auto& node : graph_.nodes) node->is_visited = false;
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
