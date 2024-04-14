#include <QApplication>
#include <cfloat>
#include <icecream.hpp>

#include "../backend/optimal_way/path_graph.h"

// #include "qcustomplot.h"

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

void CHECK_GRAPH(std::vector<TestEdge> edges, double ans) {
  PathWayGraph graph;

  std::size_t number_of_nodes = 0;
  for (auto& edge : edges)
    number_of_nodes =
        std::max(number_of_nodes, std::max(edge.node_1, edge.node_2) + 1);
  AddNodes(graph, number_of_nodes);

  for (auto& edge : edges) graph.AddEdge(edge.node_1, edge.node_2, edge.length);

  Dijkstras_algorithm da(graph);
  BOOST_TEST(da.Get_Min_Len() == ans);
}

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_1) {
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

BOOST_AUTO_TEST_CASE(test_2) {
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

BOOST_AUTO_TEST_SUITE_END()
