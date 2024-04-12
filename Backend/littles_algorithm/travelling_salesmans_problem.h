#pragma once

#include <memory>

#include "adjacency_matrix.h"
#include "tspgraph.h"

// @brief решение задачи коммивояжера
class TravellingSalesmansProblem {
 public:
  /**
   *  @brief инициализирует новый экземпляр TravellingSalesmansProblem
   *  @param matrix: матрица смежности графа
   */
  TravellingSalesmansProblem(AdjacencyMatrix& matrix);

  /**
   *  @brief инициализирует новый экземпляр TravellingSalesmansProblem для
   * нескольких коммивояжеров
   *  @param matrix: матрица смежности графа
   *  @param num_of_flyers: количество коммивояжеров
   */
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

  // Вспомогательные методы для работы с paths_stack_
  /**
   * @brief заменяет вершину графа в path_stack_ на её детей,
   * без нарушения порядка
   */
  void ExpandStack();

  /**
   * @brief удалить ребро из матрицы смежности
   * @param matrix: матрица смежности
   * @param start_num: начало ребра
   * @param end_num: конец ребра
   * @return AdjacencyMatrix матрица с удалённым ребром
   */
  AdjacencyMatrix& DeleteEdge(AdjacencyMatrix& matrix, std::size_t start_num,
                              std::size_t end_num);

  /**
   * @brief находит место для вставки вершины для соблюдения порядка
   * @param eval: нижняя оценка матрицы
   * @return std::size_t индекс вставки вершины
   */
  std::size_t FindIndex(double eval) const;

  /**
   * @brief замыкает Гамильтонов цикл обхода контрольных точек
   * @param node: вершина графа поиска оптимального пути
   */
  void CompleteEdgePath(std::shared_ptr<TSPNode> node);

  /**
   * @brief перевод ребер, содержащихся в пути
   * в последовательность обхода контрольных точек
   * @return std::vector<std::size_t> последовательность
   * обхода контрольных точек
   */
  std::vector<std::size_t> ConvertToVertexPath();

  /**
   * @brief просчитывает оптимальную маршрут
   * @return std::vector<std::size_t> порядок следования вершин
   */
  std::vector<std::size_t> CalculateTrajectory();
};
