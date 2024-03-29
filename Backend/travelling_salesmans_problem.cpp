#include "travelling_salesmans_problem.h"

#include <map>

TravellingSalesmansProblem::TravellingSalesmansProblem(AdjacencyMatrix& m) {
  paths_stack.push_back(std::make_shared<TSPNode>(m));
}

void TravellingSalesmansProblem::ExpandStack() {
  std::pair<size_t, size_t> value = paths_stack[0]->matrix.GetSelectedValue();
  std::pair<size_t, size_t> edge = paths_stack[0]->matrix.GetSelectedEdge();
  // Первый ребенок, c включением edge
  Edge included(edge, true);
  AdjacencyMatrix with_edge_matrix = paths_stack[0]->matrix.Reducted();
  with_edge_matrix.SetMatrixValue(value.second, value.first, FLT_MAX);
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
  size_t with_eval = paths_stack[0]->with_edge->evaluation;
  size_t without_eval = paths_stack[0]->without_edge->evaluation;
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

size_t TravellingSalesmansProblem::FindIndex(size_t eval) const {
  // Нижняя и верхняя границы
  size_t start = 0;
  size_t end = paths_stack.size() - 1;
  // Уменьшение области поиска
  while (start < end) {
    size_t mid = (start + end) / 2;
    // Если eval нашлось
    if (paths_stack[mid]->evaluation == eval)
      return mid + 1;
    else if (paths_stack[mid]->evaluation < eval)
      start = mid + 1;
    else
      end = mid;
  }
  return end + 1;
}

void TravellingSalesmansProblem::CompleteEdgePath() {
  Edge missed_start_edge(std::pair(0, 0), true);
  Edge missed_end_edge(std::pair(0, 0), true);
  size_t n = paths_stack[0]->matrix.GetSize();
  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      if (paths_stack[0]->matrix.GetMatrixValue(i, n) ==
          paths_stack[0]->matrix.GetMatrixValue(n, j)) {
        missed_start_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(n, j);
        missed_end_edge.start_num = paths_stack[0]->matrix.GetMatrixValue(i, n);
        if (i)
          missed_start_edge.start_num =
              paths_stack[0]->matrix.GetMatrixValue(0, n);
        else
          missed_start_edge.start_num =
              paths_stack[0]->matrix.GetMatrixValue(1, n);
        if (j)
          missed_end_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(n, 0);
        else
          missed_end_edge.end_num = paths_stack[0]->matrix.GetMatrixValue(n, 1);
      }
    }
  }
  edge_path.push_back(missed_start_edge);
  edge_path.push_back(missed_end_edge);
}

std::vector<size_t> TravellingSalesmansProblem::ConvertTosize_tPath() {
  std::map<size_t, size_t> cleared_edge_path;
  for (size_t i = 0; i < edge_path.size(); ++i) {
    if (edge_path[i].is_included)
      cleared_edge_path[edge_path[i].start_num] = edge_path[i].end_num;
  }
  std::vector<size_t> final_path;
  final_path.push_back(0);
  size_t key = 0;
  while (cleared_edge_path[key] != 0) {
    final_path.push_back(cleared_edge_path[key]);
    key = cleared_edge_path[key];
  }
  return final_path;
}

std::vector<size_t> TravellingSalesmansProblem::CalculateTrajectory() {
  while (paths_stack[0]->matrix.GetSize() > 2) ExpandStack();
  edge_path = paths_stack[0]->path;
  CompleteEdgePath();
  return ConvertTosize_tPath();
}
