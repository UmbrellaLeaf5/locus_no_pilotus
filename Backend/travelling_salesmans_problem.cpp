#include "travelling_salesmans_problem.h"

#include <map>

TravellingSalesmansProblem::TravellingSalesmansProblem(AdjacencyMatrix& m) {
  paths_stack.push_back(std::make_shared<TSPNode>(m));
}

void TravellingSalesmansProblem::ExpandStack() {
  std::pair<std::size_t, std::size_t> value =
      paths_stack[0]->matrix.GetSelectedValue();
  std::pair<std::size_t, std::size_t> edge =
      paths_stack[0]->matrix.GetSelectedEdge();
  // Первый ребенок, c включением edge
  Edge included(edge, true);
  AdjacencyMatrix with_edge_matrix = paths_stack[0]->matrix.Reducted();
  with_edge_matrix = DeleteEdge(with_edge_matrix, edge.second, edge.first);
  // Исключение возможности цикла
  for (size_t i = 0; i < paths_stack[0]->path.size(); ++i) {
    if (paths_stack[0]->path[i].start_num == edge.second) {
      with_edge_matrix = DeleteEdge(
          with_edge_matrix, paths_stack[0]->path[i].end_num, edge.first);
    }
    if (paths_stack[0]->path[i].end_num == edge.first) {
      with_edge_matrix = DeleteEdge(with_edge_matrix, edge.second,
                                    paths_stack[0]->path[i].start_num);
    }
  }
  with_edge_matrix = with_edge_matrix.Minor(value.first, value.second);
  paths_stack[0]->with_edge =
      std::make_shared<TSPNode>(with_edge_matrix, paths_stack[0], included);

  // Второй ребенок, c исключением edge
  Edge excluded(edge, false);
  AdjacencyMatrix without_edge_matrix = paths_stack[0]->matrix.Reducted();
  without_edge_matrix.SetMatrixValue(value.first, value.second, FLT_MAX);
  paths_stack[0]->without_edge =
      std::make_shared<TSPNode>(without_edge_matrix, paths_stack[0], excluded);

  // Добавляем детей в стек вершин,удаляем их родителя
  std::size_t with_eval = paths_stack[0]->with_edge->evaluation;
  std::size_t without_eval = paths_stack[0]->without_edge->evaluation;
  if (FindIndex(with_eval) < paths_stack.size())
    paths_stack.insert(paths_stack.begin() + FindIndex(with_eval),
                       paths_stack[0]->with_edge);
  else
    paths_stack.push_back(paths_stack[0]->with_edge);
  if (FindIndex(without_eval) < paths_stack.size())
    paths_stack.insert(paths_stack.begin() + FindIndex(without_eval),
                       paths_stack[0]->without_edge);
  else
    paths_stack.push_back(paths_stack[0]->without_edge);
  paths_stack.erase(paths_stack.begin());
}

AdjacencyMatrix TravellingSalesmansProblem::DeleteEdge(AdjacencyMatrix matrix,
                                                       std::size_t start_num,
                                                       std::size_t end_num) {
  for (std::size_t i = 0; i < matrix.GetSize(); ++i) {
    if (matrix.GetMatrixValue(i, matrix.GetSize()) == start_num) {
      for (std::size_t j = 0; j < matrix.GetSize(); ++j) {
        if (matrix.GetMatrixValue(matrix.GetSize(), j) == end_num) {
          matrix.SetMatrixValue(i, j, FLT_MAX);
          return matrix;
        }
      }
      return matrix;
    }
  }
  return matrix;
}

std::size_t TravellingSalesmansProblem::FindIndex(std::size_t eval) const {
  // Нижняя и верхняя границы
  std::size_t start = 0;
  std::size_t end = paths_stack.size();
  // Уменьшение области поиска
  while (start < end) {
    std::size_t mid = (start + end) / 2;
    // Если eval нашлось
    if (paths_stack[mid]->evaluation == eval)
      return mid + 1;
    else if (paths_stack[mid]->evaluation < eval)
      start = mid + 1;
    else
      end = mid;
  }
  return end;
}

void TravellingSalesmansProblem::CompleteEdgePath() {
  Edge first_missed_edge(
      std::pair(paths_stack[0]->matrix.GetMatrixValue(0, 2), 0), true);
  Edge second_missed_edge(
      std::pair(paths_stack[0]->matrix.GetMatrixValue(1, 2), 0), true);
  for (std::size_t i = 0; i < 2; ++i) {
    if (paths_stack[0]->matrix.GetMatrixValue(0, 0) <
        paths_stack[0]->matrix.GetMatrixValue(0, 1)) {
      first_missed_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(2, 0);
      second_missed_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(2, 1);
    } else {
      first_missed_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(2, 1);
      second_missed_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(2, 0);
    }
  }

  edge_path.push_back(first_missed_edge);
  edge_path.push_back(second_missed_edge);
}

std::vector<std::size_t> TravellingSalesmansProblem::ConvertToVertexPath() {
  std::map<std::size_t, std::size_t> cleared_edge_path;
  for (std::size_t i = 0; i < edge_path.size(); ++i) {
    if (edge_path[i].is_included)
      cleared_edge_path[edge_path[i].start_num] = edge_path[i].end_num;
  }
  std::vector<std::size_t> final_path;
  final_path.push_back(0);
  std::size_t key = 0;
  while (cleared_edge_path[key] != 0) {
    final_path.push_back(cleared_edge_path[key]);
    key = cleared_edge_path[key];
  }
  return final_path;
}

std::vector<std::size_t> TravellingSalesmansProblem::CalculateTrajectory() {
  while (paths_stack[0]->matrix.GetSize() > 2) ExpandStack();
  edge_path = paths_stack[0]->path;
  CompleteEdgePath();
  return ConvertToVertexPath();
}
