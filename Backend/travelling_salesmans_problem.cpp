#include "travelling_salesmans_problem.h"

TravellingSalesmansProblem::TravellingSalesmansProblem(AdjacencyMatrix& m) {
  paths_stack.push_back(std::make_shared<TSPNode>(m));
}

void TravellingSalesmansProblem::ExpandStack() {
  int with_eval = paths_stack[0]->with_edge->evaluation;
  int without_eval = paths_stack[0]->without_edge->evaluation;
  paths_stack.insert(paths_stack.begin() + FindIndex(with_eval),
                     paths_stack[0]->with_edge);
  paths_stack.insert(paths_stack.begin() + FindIndex(without_eval),
                     paths_stack[0]->without_edge);
  paths_stack.erase(paths_stack.begin());
}

size_t TravellingSalesmansProblem::FindIndex(int eval) const {
  // Lower and upper bounds
  size_t start = 0;
  size_t end = paths_stack.size() - 1;
  // Traverse the search space
  while (start <= end) {
    size_t mid = (start + end) / 2;
    // If eval is found
    if (paths_stack[mid]->evaluation == eval)
      return mid + 1;
    else if (paths_stack[mid]->evaluation < eval)
      start = mid + 1;
    else
      end = mid - 1;
  }
  // Return insert position
  return end + 1;
}
std::vector<int> TravellingSalesmansProblem::CalculateTrajectory() {
  while (paths_stack[0]->matrix->GetSize() > 2) ExpandStack();
  return std::vector<int>(0);
}
