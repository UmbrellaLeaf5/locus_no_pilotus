#pragma once

// our code libs:
#include "lib/_objects.h"
#include "math/littles_algorithm/travelling_salesmans_problem.h"
#include "math/optimal_way/optimal_way.h"

using lib::Hill;
using lib::Segment;
using lib::Target;
using lib::TrappyCircle;
using lib::TrappyLine;

namespace math {

class TrajectoryCalculator {
 public:
  /**
   * @brief Инициализирует экземпляр класса TrajectoryCalculator
   * @param targets: контрольные точки
   * @param lines: запрещённые перелеты
   * @param circles: круговые препятствия
   * @param hills: многоугольные препятствия
   */
  TrajectoryCalculator(const std::vector<Target>& targets,
                       const std::vector<TrappyLine>& lines,
                       const std::vector<TrappyCircle>& circles,
                       const std::vector<Hill>& hills) {
    for (auto& target : targets) targets_.push_back(Point(target.GetPoint()));

    forbidden_lines_ = lines;

    for (auto& circle : circles)
      circles_.push_back(
          CircleObstacle(Point(circle.GetCenter()), circle.GetRadius()));

    for (auto& hill : hills) {
      std::vector<Point> vertexes;
      for (auto& vertex : hill.GetVertices()) vertexes.push_back(Point(vertex));
      polys_.push_back(PolygonObstacle(vertexes));
    }

    CalculateTrajectory();
  }

  std::vector<Segment> GetTrajectory() { return trajectory_; }

 private:
  // Контрольные точки
  std::vector<Point> targets_;

  // Запрещенные перелёты
  std::vector<TrappyLine> forbidden_lines_;

  // Круговые препятствия
  std::vector<CircleObstacle> circles_;

  // Многоугольные препятствия
  std::vector<PolygonObstacle> polys_;

  // Траектория облета контрольных точек
  std::vector<Segment> trajectory_;

  /**
   * @brief Подсчет части траектории
   * @param optimal_way: порядок обхода точек
   * @param graph: граф, содеражщий информацию о координатах точек
   * @return Часть траектории
   */
  std::vector<Segment> GetTrajectoryPart(std::vector<std::size_t> optimal_way,
                                         const PathWayGraph& graph);

  /// @brief Расcчитывает траекторию
  void CalculateTrajectory();
};

}  // namespace math
