#pragma once

#include <map>
#include <memory>
#include <vector>

#include "circle_obstacle.h"

namespace math {

#define inf std::numeric_limits<double>::infinity()

struct Path;

struct PathWayNode {
  PathWayNode(Point p, std::size_t n)
      : point{p}, number{n}, is_visited{false} {}
  std::vector<Path> edges;
  std::shared_ptr<CircleObstacle> circle_prt = nullptr;
  Point point;
  std::size_t number;
  bool is_visited;
};

struct Path {
  Path(std::shared_ptr<PathWayNode> node_ptr, double length)
      : next{node_ptr}, length{length} {}
  std::shared_ptr<PathWayNode> next;
  double length;
};

void ConnectTwoNodes(PathWayNode& node1, PathWayNode& node2, double distance) {
  node1.edges.push_back({std::make_shared<PathWayNode>(node2), distance});
  node2.edges.push_back({std::make_shared<PathWayNode>(node1), distance});
}

// @brief алгоритм Дейкстры
class Dijkstras_algorithm {
 public:
  /**
   * @brief инициализирует новый экземпляр Dijkstras_algorithm
   * @param start: начальная точка
   * @param end: конечная точка
   */
  Dijkstras_algorithm(std::vector<PathWayNode> nodes)
      : path_nodes_{nodes},
        first_point_{nodes.size() - 2},
        second_point_{nodes.size() - 1},
        min_length_{0} {
    Calculate_Min_Path();
  }

  // Возвращает длину кратчайшего пути
  double Get_Min_Len() const { return min_length_; }

  // Возвращает последовательность точек для GUI
  // Get_Min_Path();

 private:
  // Номер первой точки
  std::size_t first_point_;

  // Номер второй точки
  std::size_t second_point_;

  // Все вершины графа
  std::vector<PathWayNode> path_nodes_;

  // Длина кратчайшего пути из start_ в end_
  double min_length_;

  // Кратчайшие найденные растояния до рассматриваемых вершин
  std::map<std::size_t, double> graphs_vertex_;

  /**
   * @brief определяет длину кратчайшего пути из start_ в end_
   */
  void Calculate_Min_Path();
};

}  // namespace math
