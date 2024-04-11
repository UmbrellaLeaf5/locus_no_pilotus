#pragma once

#include <limits>
#include <map>
#include <memory>
#include <vector>

#define inf std::numeric_limits<double>::infinity()

struct PointNode;

// Ребро взвешенного графа
struct Path {
  Path(std::shared_ptr<PointNode> point, double distance)
      : end_point{point}, length{distance} {}

  // Конец ребра
  std::shared_ptr<PointNode> end_point;
  // Длина пути
  double length;
};

// Вершина графа, обозначающая точку
struct PointNode {
  PointNode() : is_useful{true} {}

  PointNode(const PointNode& pn) {
    edges = pn.edges;
    is_useful = pn.is_useful;
  }

  PointNode operator=(const PointNode& pn) {
    edges = pn.edges;
    is_useful = pn.is_useful;
    return *this;
  }

  void AddEdge(Path edge) {
    edges.push_back(edge);
    std::shared_ptr<Path> inv_edge =
        std::make_shared<Path>(std::make_shared<PointNode>(*this), edge.length);
    (*edge.end_point).edges.push_back(*inv_edge);
  }
  // Ребра этой вершины
  std::vector<Path> edges;
  // Нужно ли ветвиться от вершины
  bool is_useful;
};

class Dijkstras_algorithm {
 public:
  Dijkstras_algorithm(std::shared_ptr<PointNode> start,
                      std::shared_ptr<PointNode> end)
      : start_{start}, end_{end}, min_length_{0} {
    graphs_vertex_[start_] = 0;
    graphs_vertex_[end_] = inf;
    Calculate_Min_Paths();
  }

  // Возвращает длину кратчайшего пути
  double Get_Min_Len() const { return min_length_; }

  // Возвращает последовательность точек для GUI
  // Get_Min_Path();

  // private:
  std::shared_ptr<PointNode> start_;
  std::shared_ptr<PointNode> end_;
  // Длина кратчайшего пути из start в end
  double min_length_;

  std::map<std::shared_ptr<PointNode>, double> graphs_vertex_;

  void Calculate_Min_Paths();
};
