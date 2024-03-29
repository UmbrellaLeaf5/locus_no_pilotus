#include "travelling_salesmans_problem.h"

TravellingSalesmansProblem::TravellingSalesmansProblem(AdjacencyMatrix& m) {
  paths_stack.push_back(std::make_shared<TSPNode>(m));
}

void TravellingSalesmansProblem::ExpandStack() {
  std::pair<int, int> value = paths_stack[0]->matrix.GetSelectedValue();
  std::pair<int, int> edge = paths_stack[0]->matrix.GetSelectedEdge();
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
  int with_eval = paths_stack[0]->with_edge->evaluation;
  int without_eval = paths_stack[0]->without_edge->evaluation;
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

size_t TravellingSalesmansProblem::FindIndex(int eval) const {
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
std::vector<int> TravellingSalesmansProblem::CalculateTrajectory() {
  while (paths_stack[0]->matrix.GetSize() > 2) ExpandStack();

  std::vector<Edge> final_path = paths_stack[0]->path;

  return std::vector<int>(0);
}
