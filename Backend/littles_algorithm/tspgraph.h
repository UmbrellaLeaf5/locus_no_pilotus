#pragma once

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "adjacency_matrix.h"

// Ребро между двумя контрольными точками
struct Edge {
  Edge(std::pair<std::size_t, std::size_t> edge)
      : start_num{edge.first}, end_num{edge.second} {}
  std::size_t start_num;
  std::size_t end_num;
};

// Вершина графа с соответствующей матрицей смежности
struct TSPNode {
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
