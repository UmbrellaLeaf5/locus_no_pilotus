#include "math/optimal_way/path_graph.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

struct TestEdge {
  std::size_t node_1;
  std::size_t node_2;
  double length;
};

void AddNodes(PathWayGraph& graph, std::size_t number_of_nodes) {
  for (std::size_t i = 0; i < number_of_nodes; ++i)
    graph.AddNode(std::make_shared<PathWayNode>(Point(0, 0), i));
}

void CHECK_GRAPH(const std::vector<TestEdge>& edges, double ans) {
  PathWayGraph graph;

  std::size_t number_of_nodes = 0;
  for (auto& edge : edges)
    number_of_nodes =
        std::max(number_of_nodes, std::max(edge.node_1, edge.node_2) + 1);
  AddNodes(graph, number_of_nodes);

  for (auto& edge : edges) graph.AddEdge(edge.node_1, edge.node_2, edge.length);

  DijkstrasAlgorithm da(graph);
  BOOST_TEST(da.Get_Min_Len() == ans);
}

BOOST_AUTO_TEST_SUITE(dijkstras_tests)

BOOST_AUTO_TEST_CASE(graph_) {
  std::vector<TestEdge> edges({{0, 5, 7},
                               {0, 6, 9},
                               {0, 7, 27},
                               {1, 2, 15},
                               {1, 3, 17},
                               {1, 6, 11},
                               {2, 3, 21},
                               {2, 7, 15},
                               {3, 8, 32},
                               {4, 5, 10},
                               {4, 6, 8},
                               {4, 8, 31}});
  double ans = 68;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_CASE(graph_1) {
  std::vector<TestEdge> edges({{0, 1, 63},
                               {0, 2, 91},
                               {0, 3, 40},
                               {1, 2, 84},
                               {1, 4, 52},
                               {2, 3, 32},
                               {2, 4, 56}});
  double ans = 88;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_CASE(graph_2) {
  std::vector<TestEdge> edges({{0, 1, 98},
                               {0, 3, 84},
                               {0, 4, 84},
                               {0, 5, 85},
                               {1, 4, 38},
                               {1, 5, 18},
                               {2, 3, 43},
                               {2, 4, 35},
                               {2, 5, 69},
                               {3, 4, 66}});
  double ans = 56;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_CASE(graph_3) {
  std::vector<TestEdge> edges({{0, 1, 51},
                               {0, 2, 259},
                               {0, 4, 215},
                               {0, 5, 84},
                               {0, 6, 24},
                               {1, 2, 45},
                               {1, 6, 90},
                               {2, 3, 287},
                               {2, 4, 27},
                               {2, 5, 97},
                               {2, 6, 214},
                               {3, 5, 160},
                               {3, 6, 170},
                               {4, 5, 93}});
  double ans = 108;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_CASE(graph_4) {
  std::vector<TestEdge> edges(
      {{0, 1, 454}, {0, 2, 308}, {0, 3, 417}, {0, 5, 329}, {0, 6, 171},
       {0, 7, 477}, {1, 3, 372}, {1, 4, 303}, {1, 5, 186}, {1, 7, 480},
       {2, 3, 37},  {2, 4, 315}, {2, 5, 57},  {2, 7, 360}, {3, 4, 478},
       {3, 6, 139}, {4, 5, 276}, {4, 6, 230}, {4, 7, 353}, {5, 6, 429}});
  double ans = 536;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_CASE(graph_5) {
  std::vector<TestEdge> edges(
      {{0, 1, 444}, {0, 2, 289}, {0, 4, 182}, {0, 7, 124}, {0, 9, 293},
       {1, 2, 272}, {1, 4, 371}, {1, 6, 253}, {1, 7, 243}, {1, 8, 215},
       {1, 9, 202}, {2, 3, 465}, {2, 4, 255}, {2, 6, 84},  {2, 7, 49},
       {2, 9, 171}, {3, 4, 234}, {3, 5, 154}, {3, 6, 49},  {3, 7, 374},
       {3, 8, 41},  {3, 9, 422}, {4, 9, 424}, {5, 7, 361}, {6, 8, 148}});
  double ans = 345;
  CHECK_GRAPH(edges, ans);
}

BOOST_AUTO_TEST_SUITE_END()
