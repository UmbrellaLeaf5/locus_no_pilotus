// header file:
#include "trajectory.h"

namespace math {

std::vector<Segment> TrajectoryCalculator::GetTrajectoryPart(
    std::vector<std::size_t> optimal_way, const PathWayGraph& graph) {
  std::vector<Segment> trajectory_part;
  for (std::size_t i = 0; i < optimal_way.size() - 1; ++i) {
    // Если точки ляжат на одной окружности, их следует соединить дугой
    if ((graph.nodes[optimal_way[i]]->circle_ptr) &&
        (graph.nodes[optimal_way[i] + 1]->circle_ptr) &&
        (graph.nodes[optimal_way[i]]->circle_ptr ==
         graph.nodes[optimal_way[i] + 1]->circle_ptr))
      trajectory_part.push_back(
          Segment(graph.nodes[optimal_way[i]]->point,
                  graph.nodes[optimal_way[i] + 1]->point,
                  graph.nodes[optimal_way[i]]->circle_ptr->GetCenter()));
    else {
      trajectory_part.push_back(
          Segment(graph.nodes[optimal_way[i]]->point,
                  graph.nodes[optimal_way[i] + 1]->point));
    }
  }
  return trajectory_part;
}

void TrajectoryCalculator::CalculateTrajectory() {
  std::vector<std::vector<double>> matrix(targets_.size());
  for (auto& elem : matrix) elem.resize(targets_.size());

  std::vector<std::vector<std::vector<Segment>>> optimal_ways(targets_.size());
  for (auto& elem : optimal_ways) elem.resize(targets_.size());

  OptimalWayCalculator owc(circles_, polys_);

  for (std::size_t i = 0; i < targets_.size() - 1; ++i) {
    matrix[i][i] = inf;
    for (std::size_t j = i + 1; i < targets_.size(); ++j) {
      std::vector<std::size_t> optimal_way =
          owc.GetOptimalWay(targets_[i], targets_[j]);
      PathWayGraph graph = owc.GetGraph();

      std::vector<Segment> segment_way = GetTrajectoryPart(optimal_way, graph);
      optimal_ways[i][j] = segment_way;
      std::reverse(segment_way.begin(), segment_way.begin());
      optimal_ways[j][i] = segment_way;

      matrix[i][j] = owc.GetOptimalWayLength();
      matrix[j][i] = owc.GetOptimalWayLength();
    }
  }
}

}  // namespace math
