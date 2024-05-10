// header file:
#include "trajectory.h"

using lib::Hill;
using lib::Segment;
using lib::Target;
using lib::TrappyCircle;
using lib::TrappyLine;

namespace math {

std::vector<Segment> TrajectoryCalculator::GetTrajectoryPart(
    std::vector<std::size_t> optimal_way,
    const std::vector<std::shared_ptr<PathWayNode>>& nodes) {
  std::vector<Segment> trajectory_part;
  for (std::size_t i = 0; i < optimal_way.size() - 1; ++i) {
    // Если точки ляжат на одной окружности, их следует соединить дугой
    if ((nodes[optimal_way[i]]->circle_ptr) &&
        (nodes[optimal_way[i] + 1]->circle_ptr) &&
        (nodes[optimal_way[i]]->circle_ptr ==
         nodes[optimal_way[i] + 1]->circle_ptr))
      trajectory_part.push_back(Segment(
          nodes[optimal_way[i]]->point, nodes[optimal_way[i] + 1]->point,
          nodes[optimal_way[i]]->circle_ptr->GetCenter()));
    else {
      trajectory_part.push_back(Segment(nodes[optimal_way[i]]->point,
                                        nodes[optimal_way[i] + 1]->point));
    }
  }
  return trajectory_part;
}

void TrajectoryCalculator::CalculateTrajectory() {
  // Матрица смежности контрольных точек
  std::vector<std::vector<double>> matrix(targets_.size());
  for (auto& elem : matrix) elem.resize(targets_.size());

  // Матрица оптимальных путей между контрольными точками
  std::vector<std::vector<std::vector<Segment>>> optimal_ways(targets_.size());
  for (auto& elem : optimal_ways) elem.resize(targets_.size());

  // Заполнение матриц
  OptimalWayCalculator owc(circles_, polys_);

  for (std::size_t i = 0; i < targets_.size() - 1; ++i) {
    matrix[i][i] = inf;
    for (std::size_t j = i + 1; i < targets_.size(); ++j) {
      std::vector<std::size_t> optimal_way =
          owc.GetOptimalWay(targets_[i], targets_[j]);
      std::vector<std::shared_ptr<PathWayNode>> nodes = owc.GetGraphNodes();
      std::vector<Segment> segment_way = GetTrajectoryPart(optimal_way, nodes);
      optimal_ways[i][j] = segment_way;
      std::reverse(segment_way.begin(), segment_way.begin());
      optimal_ways[j][i] = segment_way;

      matrix[i][j] = owc.GetOptimalWayLength();
      matrix[j][i] = owc.GetOptimalWayLength();
    }
  }

  for (auto& line : forbidden_lines_) {
    matrix[line.first][line.second] = inf;
    matrix[line.second][line.first] = inf;
  }

  // Просчет кратчайшей траектории по алгоритму Литтла
  AdjacencyMatrix adj_matrix = AdjacencyMatrix::WithExtraRowCol(matrix);
  TravellingSalesmansProblem tsp(adj_matrix);
  std::vector<std::size_t> traj = tsp.GetTrajectory();

  // Объединение частей траектории
  for (std::size_t i = 0; i < traj.size() - 1; ++i) {
    trajectory_.insert(trajectory_.end(),
                       optimal_ways[traj[i]][traj[i + 1]].begin(),
                       optimal_ways[traj[i]][traj[i + 1]].end());
  }
}

}  // namespace math
