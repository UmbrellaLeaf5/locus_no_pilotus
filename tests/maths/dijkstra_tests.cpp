#include <QApplication>

#include "../backend/dijkstras_algorithm/points_graph.h"
#include "../icecream-cpp/icecream.hpp"

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_1) {
  std::shared_ptr<PointNode> A;
  std::shared_ptr<PointNode> B;
  // std::shared_ptr<PointNode> S;
  // std::shared_ptr<PointNode> M;
  // std::shared_ptr<PointNode> D;
  // std::shared_ptr<PointNode> R;
  // std::shared_ptr<PointNode> N;
  // std::shared_ptr<PointNode> L;
  // std::shared_ptr<PointNode> G;
  Path AB(B, 27);
  (*A).edges.push_back(AB);
  // Path AM(M, 15);
  // Path BL(L, 7);
  // Path BG(G, 9);
  // Path SM(M, 15);
  // Path SD(D, 17);
  // Path SG(G, 11);
  // Path MD(D, 21);
  // Path DR(R, 32);
  // Path RN(N, 31);
  // Path NL(L, 10);
  // Path NG(G, 8);
  // for (auto& elem : (*A).edges) {
  // IC((*AB).length);
  // }
  // Dijkstras_algorithm da(A, R);
  // while (da.graphs_vertex_[da.end_] > da.min_length_) {
  //   std::shared_ptr<PointNode> min_len_key;
  //   for (auto& elem : da.graphs_vertex_)
  //     if ((elem.second == da.min_length_) && ((*elem.first).is_useful))
  //       min_len_key = elem.first;
  // for (auto& elem : (*min_len_key).edges)
  // if ((da.graphs_vertex_.find(elem.end_point) == da.graphs_vertex_.end())
  // ||
  //     (elem.length + da.graphs_vertex_[min_len_key] <
  //      da.graphs_vertex_[elem.end_point])) {
  //   da.graphs_vertex_[elem.end_point] =
  //       elem.length + da.graphs_vertex_[min_len_key];
  //   (*elem.end_point).is_useful = true;
  // } else {
  //   (*elem.end_point).is_useful = false;
  //   continue;
  // }
  // da.min_length_ = inf;
  // (*min_len_key).is_useful = false;
  // for (auto& elem : da.graphs_vertex_) {
  //   IC(elem.second);
  //   if ((elem.second < da.min_length_) && ((*elem.first).is_useful))
  //     da.min_length_ = elem.second;
  //
  // IC(da.Get_Min_Len());
}
BOOST_AUTO_TEST_SUITE_END()
