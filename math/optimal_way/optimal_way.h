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
   * @param v: круговые препятствия
   */
  MinimumDistanceCalculator(Point p1, Point p2, std::vector<CircleObstacle> v)
      : point1_{p1}, point2_{p2}, circles_{v} {
    FindOptimalWay();
  }

  std::vector<std::size_t> GetOptimalWay() { return optimal_way_; }

 private:
  Point point1_;

  Point point2_;

  std::vector<CircleObstacle> circles_;

  // Граф для алгоритма Дейкстры
  PathWayGraph graph_;

  // Оптимальный путь
  std::vector<std::size_t> optimal_way_;

  /**
   * @brief Проверяет, пересекает ли общая касательная двух кругов другой круг
   * @param tangent: общая касательная
   * @param circle1_index: номер круга 1
   * @param circle2_index: номер круга 2
   * @return bool: результат проверки
   */
  bool TangentGoesTroughOtherCircle(const LinearFunction& tangent,
                                    int circle1_index, int circle2_index);

  /**
   * @brief Добавляет информацию об общей касательной двух кругов
   * @param tangent: общая касательная
   * @param circle1: круг 1
   * @param circle2: круг 2
   */
  void AddTangent(const LinearFunction& tangent, CircleObstacle& circle1,
                  CircleObstacle& circle2);

  // Добавляет информацию о всех общих касательных всех окружностей
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
