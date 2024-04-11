#include "points_graph.h"

#include "../icecream-cpp/icecream.hpp"

void Dijkstras_algorithm::Calculate_Min_Paths() {
  while (graphs_vertex_[end_] > min_length_) {
    std::shared_ptr<PointNode> min_len_key;
    for (auto&& elem : graphs_vertex_)
      if ((elem.second == min_length_) && ((*elem.first).is_useful))
        min_len_key = elem.first;
    min_length_ = inf;
    for (auto& elem : (*min_len_key).edges)
      if ((graphs_vertex_.find(elem.end_point) == graphs_vertex_.end()) ||
          (elem.length + graphs_vertex_[min_len_key] <
           graphs_vertex_[elem.end_point])) {
        graphs_vertex_[elem.end_point] =
            elem.length + graphs_vertex_[min_len_key];
        (*elem.end_point).is_useful = true;
      } else {
        (*elem.end_point).is_useful = false;
        continue;
      }
    min_length_ = inf;
    (*min_len_key).is_useful = false;
    for (auto& elem : graphs_vertex_) {
      if ((elem.second < min_length_) && ((*elem.first).is_useful))
        min_length_ = elem.second;
    }
  }
}
