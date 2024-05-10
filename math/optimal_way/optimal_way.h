#pragma once

// our code libs:
#include "path_graph.h"

namespace math {

/// @brief Функтор, находящий кратчайший путь между точками
class OptimalWayCalculator {
 public:
  /**
   * @brief Находит кратчайший путь между точками
   * @param circles: круговые препятствия
   * @param polys: многоугольные препятствия
   */
  OptimalWayCalculator(const std::vector<CircleObstacle>& circles,
                       const std::vector<PolygonObstacle>& polys)
      : circles_{circles}, polys_{polys} {
    AddCommonTangents();
    AddGraphTangentPoints();
    normal_graph_size_ = graph_.nodes.size();
  }

  std::vector<std::shared_ptr<PathWayNode>> GetGraphNodes() {
    return graph_.nodes;
  }

  std::vector<std::size_t> GetOptimalWay(Point point1, Point point2) {
    FindOptimalWay(point1, point2);
    return optimal_way_;
  }

  double GetOptimalWayLength() { return optimal_way_length_; }

 private:
  std::vector<CircleObstacle> circles_;

  std::vector<PolygonObstacle> polys_;

  // Граф для алгоритма Дейкстры
  PathWayGraph graph_;

  // Количество вершин в графе без связей с контрольными точками
  std::size_t normal_graph_size_;

  // Оптимальный путь
  std::vector<std::size_t> optimal_way_;

  // Длина оптимального пути
  double optimal_way_length_;

  /**
   * @brief Проверяет, пересекает ли общая касательная двух препятствий другое
   * препятствие
   * @param tangent: общая касательная
   * @param obstacle1: номер препятствие 1
   * @param obstacle2: номер препятствие 2
   * @return bool: результат проверки
   */
  template <typename T, typename U>
  bool TangentGoesThroughOtherObstacle(const LinearFunction& tangent,
                                       T& obstacle1, U& obstacle2);

  /**
   * @brief Проверяет, пересекает ли касательная препятствие
   * @param tangent_point: точка касания
   * @param control_point: контрольная точка
   * @return результат проверки
   */
  bool TangentGoesThroughOtherObstacle(const Point& tangent_point,
                                       const Point& control_point);

  /**
   * @brief Добавляет информацию об общей касательной двух препятствий
   * @param tangent: общая касательная
   * @param obstacle1: препятствие 1
   * @param obstacle2: препятствие 2
   */
  template <typename T, typename U>
  void AddTangent(const LinearFunction& tangent, T& obstacle1, U& obstacle2);

  // Добавляет информацию о всех общих касательных всех препятствий
  void AddCommonTangents();

  // Добавляет в граф точки касания
  void AddGraphTangentPoints();

  // Добавляет в граф контрольные точки
  std::size_t AddGraphControlPoints(Point point);

  // Находит оптимальный маршрут
  void FindOptimalWay(Point p1, Point p2);
};

}  // namespace math
