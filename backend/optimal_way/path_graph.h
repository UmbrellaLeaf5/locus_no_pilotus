#pragma once

#include <map>
#include <memory>
#include <vector>

#include "circle_obstacle.h"

namespace math {

#define inf std::numeric_limits<double>::infinity()

struct PathWayNode {
  PathWayNode(Point p, std::size_t n)
      : point{p}, number{n}, is_visited{false} {}
  std::vector<std::shared_ptr<PathWayNode>> edges;
  std::vector<double> edges_lens;
  std::shared_ptr<CircleObstacle> circle_prt = nullptr;
  Point point;
  std::size_t number;
  bool is_visited;
};

struct PathWayGraph {
  std::vector<std::shared_ptr<PathWayNode>> nodes;

  void AddNode(std::shared_ptr<PathWayNode> new_node) {
    nodes.push_back(new_node);
  }

  void AddEdge(std::size_t node_1, std::size_t node_2, double length) {
    std::shared_ptr<PathWayNode> node_ptr1, node_ptr2;

    for (auto node : nodes) {
      if (node->number == node_1)
        node_ptr1 = node;
      else if (node->number == node_2)
        node_ptr2 = node;
    }

    node_ptr1->edges.push_back(node_ptr2);
    node_ptr1->edges_lens.push_back(length);
    node_ptr2->edges.push_back(node_ptr1);
    node_ptr2->edges_lens.push_back(length);
  }
};

/// @brief алгоритм Дейкстры
class Dijkstras_algorithm {
 public:
  /**
   * @brief инициализирует новый экземпляр Dijkstras_algorithm
   * @param start: начальная точка
   * @param end: конечная точка
   */
  Dijkstras_algorithm(PathWayGraph graph)
      : path_nodes_{graph.nodes},
        first_point_{graph.nodes.size() - 2},
        second_point_{graph.nodes.size() - 1},
        min_length_{0} {
    graphs_vertex_[first_point_] = 0;
    graphs_vertex_[second_point_] = inf;
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
  std::vector<std::shared_ptr<PathWayNode>> path_nodes_;

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
