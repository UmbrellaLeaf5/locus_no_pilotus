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
  TSPNode(AdjacencyMatrix& m, std::optional<Edge> new_edge = std::nullopt)
      : evaluation{m.GetBottomLineEvaluation()} {
    *matrix = m;
    if (new_edge) path.push_back(*new_edge);
    // Вершина графа рекурсивно создает своих детей
    // FIX: Это действие нужно совершать только для вершины
    // c минимальной нижней оценкой (лежащей в paths_stack[0]
    // в классе TSP) в целях оптимизации алгоритма
    if (m.GetSize() > 2) {
      std::pair<int, int> edge = m.GetSelectedEdge();
      AdjacencyMatrix with_edge_matrix = *matrix;
      with_edge_matrix.SetMatrixValue(edge.second, edge.first, FLT_MAX);
      with_edge_matrix = with_edge_matrix.Minor(edge.first, edge.second);
      with_edge = std::make_unique<TSPNode>(with_edge_matrix);

      AdjacencyMatrix without_edge_matrix = *matrix;
      without_edge_matrix.SetMatrixValue(edge.first, edge.second, FLT_MAX);
      without_edge_matrix.SetMatrixValue(edge.second, edge.first, FLT_MAX);
      without_edge = std::make_unique<TSPNode>(without_edge_matrix);
    }
  }

  std::shared_ptr<TSPNode> with_edge = nullptr;
  std::shared_ptr<TSPNode> without_edge = nullptr;
  std::unique_ptr<AdjacencyMatrix> matrix;
  float evaluation;
  std::vector<Edge> path;
};
