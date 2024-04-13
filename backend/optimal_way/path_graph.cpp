#include "path_graph.h"

namespace math {

void Dijkstras_algorithm::Calculate_Min_Path() {
  while (graphs_vertex_[second_point_] > min_length_) {
    std::shared_ptr<PathWayNode> min_len_key;
    for (auto& elem : graphs_vertex_)
      if ((elem.second == min_length_) &&
          (!(*path_nodes_[elem.first]).is_visited))
        min_len_key = path_nodes_[elem.first];

    for (std::size_t i = 0; i < (*min_len_key).edges.size(); ++i)
      if ((graphs_vertex_.find((*(*min_len_key).edges[i]).number) ==
           graphs_vertex_.end()) ||
          (graphs_vertex_[(*(*min_len_key).edges[i]).number] >
           graphs_vertex_[(*min_len_key).number] +
               (*min_len_key).edges_lens[i]))
        graphs_vertex_[(*(*min_len_key).edges[i]).number] =
            graphs_vertex_[(*min_len_key).number] +
            (*min_len_key).edges_lens[i];
      else
        continue;
    (*min_len_key).is_visited = true;

    min_length_ = inf;
    for (auto& elem : graphs_vertex_)
      if ((elem.second < min_length_) &&
          (!(*path_nodes_[elem.first]).is_visited))
        min_length_ = elem.second;
  }
}

}  // namespace math
