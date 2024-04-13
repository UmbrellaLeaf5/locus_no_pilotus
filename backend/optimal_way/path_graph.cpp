#include "path_graph.h"

#include <icecream.hpp>

namespace math {

void Dijkstras_algorithm::Calculate_Min_Path() {
  while (graphs_vertex_[second_point_] > min_length_) {
    IC(graphs_vertex_[second_point_]);
    std::shared_ptr<PathWayNode> min_len_key;
    for (auto& elem : graphs_vertex_)
      if ((elem.second == min_length_) && (!path_nodes_[elem.first].is_visited))
        min_len_key = std::make_shared<PathWayNode>(path_nodes_[elem.first]);

    for (auto& elem : (*min_len_key).edges) {
      IC(elem.length);
      if ((graphs_vertex_.find((*elem.next).number) == graphs_vertex_.end()) ||
          (elem.length + graphs_vertex_[(*min_len_key).number] <
           graphs_vertex_[(*elem.next).number])) {
        graphs_vertex_[(*elem.next).number] =
            elem.length + graphs_vertex_[(*min_len_key).number];
      } else
        continue;
    }
    (*min_len_key).is_visited = true;

    min_length_ = inf;
    for (auto& elem : graphs_vertex_) {
      IC(elem.second);
      if ((elem.second < min_length_) &&
          (!path_nodes_[elem.first].is_visited)) {
        IC(elem.second);
        min_length_ = elem.second;
      }
    }
  }
}

}  // namespace math
