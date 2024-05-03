#pragma once

#include <vector>

#include "path_graph.h"

namespace math {

/// @brief Функтор, находящий кратчайший путь между точками
class MinimumDistanceCalculator {
 public:
  /**
   * @brief Находит кратчайший путь между точками
   * @param p1: точка 1
   * @param p2: точка 2
   * @param circles: круговые препятствия
   * @param polys: многоугольные препятствия
   */
  MinimumDistanceCalculator(Point p1, Point p2,
                            std::vector<CircleObstacle> circles,
                            std::vector<PolygonObstacle> polys)
      : point1_{p1}, point2_{p2}, circles_{circles}, polys_{polys} {
    FindOptimalWay();
  }

  std::vector<std::size_t> GetOptimalWay() { return optimal_way_; }

 private:
  Point point1_;

  Point point2_;

  std::vector<CircleObstacle> circles_;

  std::vector<PolygonObstacle> polys_;

  // Граф для алгоритма Дейкстры
  PathWayGraph graph_;

  // Оптимальный путь
  std::vector<std::size_t> optimal_way_;

  /**
   * @brief Проверяет, пересекает ли общая касательная двух препятствий другое
   * препятствие
   * @param tangent: общая касательная
   * @param circle1_index: номер препятствие 1
   * @param circle2_index: номер препятствие 2
   * @return bool: результат проверки
   */
  template <typename T, typename U>
  bool TangentGoesTroughOtherObstacle(const LinearFunction& tangent,
                                      T& obstacle1, U& obstacle2);

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

  // Добавляет информацию о всех касательных из контрольных точек
  void AddControlPointTangents();

  // Добавляет в граф точки касания
  void AddGraphTangentPoints();

  // Добавляет в граф контрольные точки
  void AddGraphControlPoints();

  // Находит оптимальный маршрут
  void FindOptimalWay();
};

}  // namespace math
