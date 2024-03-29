#pragma once

#include <memory>

#include "adjacency_matrix.h"
#include "tspgraph.h"

// Класс, решающий задачу коммивояжера
class TravellingSalesmansProblem {
 public:
  TravellingSalesmansProblem(AdjacencyMatrix& matrix);

  // Возвращает оптимальный маршрут для данной задачи
  inline std::vector<int> GetTrajectory() { return CalculateTrajectory(); }

 private:
  // Вектор с указателями на вершины графа
  // Отсортирован в порядке возрастания нижней оценки
  std::vector<std::shared_ptr<TSPNode>> paths_stack;

  // Ребра получившегося маршрута
  std::vector<Edge> edge_path;

  // Вспомогательные методы для работы с paths_stack
  // Заменяет вершину графа на её детей, без нарушения порядка
  void ExpandStack();

  // Находит место для вставки вершины
  size_t FindIndex(int eval) const;

  // Замыкает Гамильтонов цикл обхода
  void CompleteEdgePath();

  // Перевод ребер, содержащихся в пути в
  // последовательность обхода вершин
  std::vector<int> ConvertToIntPath();

  // Возвращает порядок следования вершин в оптимальном маршруте
  // TODO: Научится порядок следования вершин в маршруте,
  // зная запрещенные и обязательные ребра
  std::vector<int> CalculateTrajectory();
};
