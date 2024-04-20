#include "optimal_way.h"

#include "helpers_functions.h"

namespace math {

bool MinimumDistanceCalculator::TangentGoesTroughOtherCircle(
    const LinearFunction& tangent, int circle1_index, int circle2_index) {
  std::pair<Point, Point> tangent_points =
      TangentPoints(tangent, circles_[circle1_index], circles_[circle2_index]);
  for (int l = 0; l < circles_.size(); ++l)
    if (l != circle1_index && l != circle2_index)
      if (AreThereIntersections(circles_[l], tangent_points.first,
                                tangent_points.second))
        return true;
  return false;
}

void MinimumDistanceCalculator::AddTangent(const LinearFunction& tangent,
                                           CircleObstacle& circle1,
                                           CircleObstacle& circle2) {
  std::pair<Point, Point> tangent_points =
      TangentPoints(tangent, circle1, circle2);
  tangent_points.first.another_tangent_point =
      std::make_shared<Point>(tangent_points.second);
  tangent_points.second.another_tangent_point =
      std::make_shared<Point>(tangent_points.first);
  circle1.AddTangentLine(tangent);
  circle1.AddTangentPoint(tangent_points.first);
  circle2.AddTangentLine(tangent);
  circle2.AddTangentPoint(tangent_points.second);
}

void MinimumDistanceCalculator::AddCommonTangents() {
  for (int i = 0; i < circles_.size(); ++i) {
    for (int j = i + 1; j < circles_.size(); ++j) {
      std::vector<LinearFunction> tangents =
          TangentsBetweenCircles(circles_[i], circles_[j]);

      for (int k = 0; k < tangents.size(); ++k)
        if (!TangentGoesTroughOtherCircle(tangents[k], i, j))
          AddTangent(tangents[k], circles_[i], circles_[j]);
    }
  }
}

void MinimumDistanceCalculator::AddControlPointTangents() {
  for (auto point : {point1_, point2_})
    for (int i = 0; i < circles_.size(); ++i) {
      std::pair<Point, Point> tangent_points_1 =
          TangentPointsToCircle(circles_[i], point);
      bool is_exist_tangent1 = true;
      bool is_exist_tangent2 = true;
      for (int j = 0; j < circles_.size(); ++j) {
        if (j != i) {
          if (AreThereIntersections(circles_[j], point, tangent_points_1.first))
            is_exist_tangent1 = false;
          if (AreThereIntersections(circles_[j], point,
                                    tangent_points_1.second))
            is_exist_tangent2 = false;
        }
      }
      if (is_exist_tangent1)
        point.tangents.push_back(LinearFunction(point, tangent_points_1.first));

      if (is_exist_tangent2)
        point.tangents.push_back(
            LinearFunction(point, tangent_points_1.second));
    }
}

void MinimumDistanceCalculator::AddGraphTangentPoints() {
  for (auto& obstacle : circles_) {
    for (auto& point : obstacle.GetTangentPoints()) {
      PathWayNode new_node{point, graph_.nodes.size()};
      new_node.circle_prt = std::make_unique<CircleObstacle>(obstacle);
      for (auto& prev : graph_.nodes) {
        if ((*prev).circle_prt && ((*(*prev).circle_prt) == obstacle)) {
          graph_.AddEdge((*prev).number, new_node.number,
                         DistanceBetweenPointsOnCircle(obstacle, (*prev).point,
                                                       new_node.point));
        } else if ((*prev).circle_prt &&
                   (new_node.point == (*(*prev).point.another_tangent_point))) {
          graph_.AddEdge((*prev).number, new_node.number,
                         DistanceBetweenPoints((*prev).point, new_node.point));
        }
      }
      graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
    }
  }
}

void MinimumDistanceCalculator::AddGraphControlPoints() {
  for (auto point : {point1_, point2_}) {
    PathWayNode new_node{point, graph_.nodes.size()};
    for (auto& prev : graph_.nodes) {
      if ((*prev).circle_prt) {
        std::pair<Point, Point> tangent_points =
            TangentPointsToCircle((*(*prev).circle_prt), point);
        if (tangent_points.first == (*prev).point ||
            tangent_points.second == (*prev).point) {
          graph_.AddEdge((*prev).number, new_node.number,
                         DistanceBetweenPoints((*prev).point, new_node.point));
        }
      }
    }
    graph_.nodes.push_back(std::make_shared<PathWayNode>(new_node));
  }
}

void MinimumDistanceCalculator::FindOptimalWay() {
  AddCommonTangents();
  AddControlPointTangents();
  AddGraphTangentPoints();
  AddGraphControlPoints();
  DijkstrasAlgorithm da(graph_);
  optimal_way_ = da.Get_Min_Path();
}

}  // namespace math
