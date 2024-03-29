#pragma once

#include <cfloat>
#include <memory>
#include <optional>
#include <vector>

#include "adjacency_matrix.h"

// Ребро между двумя контрольными точками
struct Edge {
  Edge(std::pair<int, int> edge, bool state)
      : start_num{edge.first}, end_num{edge.second}, is_included{state} {}
  int start_num;
  int end_num;
  bool is_included;
};

// Вершина графа с соответствующей матрицей смежности
struct TSPNode {
  TSPNode(AdjacencyMatrix& m,
          std::optional<std::shared_ptr<TSPNode>> prev_node = std::nullopt,
          std::optional<Edge> new_edge = std::nullopt)
      : matrix{m}, evaluation{m.GetBottomLineEvaluation()} {
    if (prev_node) {
      evaluation += (**prev_node).evaluation;
      path = (**prev_node).path;
    }
    if (new_edge) path.push_back(*new_edge);
  }

  std::shared_ptr<TSPNode> with_edge = nullptr;
  std::shared_ptr<TSPNode> without_edge = nullptr;
  AdjacencyMatrix matrix;
  double evaluation;
  std::vector<Edge> path;
};
