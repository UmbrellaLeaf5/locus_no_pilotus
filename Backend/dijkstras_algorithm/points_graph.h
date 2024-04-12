#pragma once

#include <limits>
#include <map>
#include <memory>
#include <vector>

namespace math {

#define inf std::numeric_limits<double>::infinity()

struct PointNode;

// @brief путь в вершину
struct Path {
  /**
   * @brief инициализирует новый экземпляр Path
   * @param point: конечная точка
   * @param distance: длина пути
   */
  Path(std::shared_ptr<PointNode> point, double distance)
      : end_point{point}, length{distance} {}

  // Конец ребра
  std::shared_ptr<PointNode> end_point;

  // Длина пути
  double length;
};

// @brief вершина графа, обозначающая точку
struct PointNode {
  PointNode() : is_useful{true} {}

  /**
   * @brief добавить путь
   * @param path: путь
   */
  void AddPath(Path path) {
    paths.push_back(path);
    std::shared_ptr<Path> inv_path =
        std::make_shared<Path>(std::make_shared<PointNode>(*this), path.length);
    (*path.end_point).paths.push_back(*inv_path);
  }

  // Ребра этой вершины
  std::vector<Path> paths;

  // Нужно ли ветвиться от вершины
  bool is_useful;
};

// Ребро взвешенного графа
struct Edge {
  /**
   * @brief добавляет ребро взвешенного графа
   * @param point_1: первая точка
   * @param point_2: вторая точка
   * @param length: длина ребра
   */
  Edge(std::shared_ptr<PointNode> point_1, std::shared_ptr<PointNode> point_2,
       double length) {
    (*point_1).AddPath(Path(point_2, length));
  }
};

// @brief алгоритм Дейкстры
class Dijkstras_algorithm {
 public:
  /**
   * @brief инициализирует новый экземпляр Dijkstras_algorithm
   * @param start: начальная точка
   * @param end: конечная точка
   */
  Dijkstras_algorithm(std::shared_ptr<PointNode> start,
                      std::shared_ptr<PointNode> end)
      : start_{start}, end_{end}, min_length_{0} {
    graphs_vertex_[start_] = 0;
    graphs_vertex_[end_] = inf;
    Calculate_Min_Path();
  }

  // Возвращает длину кратчайшего пути
  double Get_Min_Len() const { return min_length_; }

  // Возвращает последовательность точек для GUI
  // Get_Min_Path();

 private:
  // Начальная точка
  std::shared_ptr<PointNode> start_;

  // Конечная точка
  std::shared_ptr<PointNode> end_;

  // Длина кратчайшего пути из start_ в end_
  double min_length_;

  // Кратчайшие найденные растояния до рассматриваемых вершин
  std::map<std::shared_ptr<PointNode>, double> graphs_vertex_;

  /**
   * @brief определяет длинукратчайшего пути из start_ в end_
   */
  void Calculate_Min_Path();
};

}  // namespace math
