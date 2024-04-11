#pragma once

#include <memory>

#include "adjacency_matrix.h"
#include "tspgraph.h"

// Класс, решающий задачу коммивояжера
class TravellingSalesmansProblem {
 public:
  TravellingSalesmansProblem(AdjacencyMatrix& matrix);

  // Для нескольких коммивояжеров
  TravellingSalesmansProblem(AdjacencyMatrix& matrix,
                             std::size_t num_of_flyers);

  // Возвращает оптимальный маршрут для данной задачи
  inline std::vector<std::size_t> GetTrajectory() {
    return CalculateTrajectory();
  }

 private:
  // Количество коммивояжеров
  std::size_t num_of_flyers_;
  // Вектор с указателями на вершины графа
  // Отсортирован в порядке возрастания нижней оценки
  std::vector<std::shared_ptr<TSPNode>> paths_stack_;

  // Ребра получившегося маршрута
  std::vector<Edge> edge_path_;

  // Возвращает количество коммивояжеров
  std::size_t GetNumOfFlyers() const { return num_of_flyers_; }

  // Вспомогательные методы для работы с paths_stack_
  // Заменяет вершину графа на её детей, без нарушения порядка
  void ExpandStack();

  // Удалить ребро из матрицы смежности
  AdjacencyMatrix DeleteEdge(AdjacencyMatrix matrix, std::size_t start_num,
                             std::size_t end_num);

  // Находит место для вставки вершины
  std::size_t FindIndex(double eval) const;

  // Замыкает Гамильтонов цикл обхода
  void CompleteEdgePath(std::shared_ptr<TSPNode> node);

  // Перевод ребер, содержащихся в пути в
  // последовательность обхода вершин
  std::vector<std::size_t> ConvertToVertexPath();

  // Возвращает порядок следования вершин в оптимальном маршруте
  std::vector<std::size_t> CalculateTrajectory();
};
