#pragma once

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "adjacency_matrix.h"

namespace math {

/// @brief Ребро между двумя контрольными точками
struct Edge {
  /**
   * @brief Создает новый экземпляр Edge
   * @param edge: упорядоченная пара точек
   */
  Edge(std::pair<std::size_t, std::size_t> edge)
      : start_num{edge.first}, end_num{edge.second} {}
  std::size_t start_num;
  std::size_t end_num;
};

/// @brief Вершина дерева с соответствующей матрицей смежности
struct TSPNode {
  /**
   * @brief Создает новый экземпляр TSPNode
   * @param m: матрица смежности
   * @param prev_node: родитель вершины
   * @param new_edge: новое ребро маршрута
   * @param graph_chains: завершенные цепи в уже существующем маршруте
   */
  TSPNode(AdjacencyMatrix& m,
          std::optional<std::shared_ptr<TSPNode>> prev_node = std::nullopt,
          std::optional<Edge> new_edge = std::nullopt,
          std::optional<std::map<std::size_t, std::size_t>> graph_chains =
              std::nullopt)
      : matrix{m}, evaluation{m.GetBottomLineEvaluation()} {
    if (prev_node) {
      evaluation += (**prev_node).evaluation;
      path = (**prev_node).path;
      if (graph_chains)
        chains = *graph_chains;
      else
        chains = (**prev_node).chains;
    }
    if (new_edge) path.push_back(*new_edge);
  }

  std::shared_ptr<TSPNode> with_edge = nullptr;
  std::shared_ptr<TSPNode> without_edge = nullptr;
  AdjacencyMatrix matrix;
  double evaluation;
  std::vector<Edge> path;
  std::map<std::size_t, std::size_t> chains;
};

}  // namespace math
