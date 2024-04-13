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

void CreateNodes(PathWayGraph& graph, std::size_t number_of_nodes) {
  for (std::size_t i = 0; i < number_of_nodes; ++i)
    graph.nodes.push_back(std::make_shared<PathWayNode>(Point(0, 0), i));
}

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_1) {
  PathWayGraph graph;
  CreateNodes(graph, 9);
  graph.AddEdge(0, 5, 7);
  graph.AddEdge(0, 6, 9);
  graph.AddEdge(0, 7, 27);
  graph.AddEdge(1, 2, 15);
  graph.AddEdge(1, 3, 17);
  graph.AddEdge(1, 6, 11);
  graph.AddEdge(2, 3, 21);
  graph.AddEdge(2, 7, 15);
  graph.AddEdge(3, 8, 32);
  graph.AddEdge(4, 5, 10);
  graph.AddEdge(4, 6, 8);
  graph.AddEdge(4, 8, 31);
  double ans = 68;
  Dijkstras_algorithm da(graph);
  BOOST_TEST(da.Get_Min_Len() == ans);
}

BOOST_AUTO_TEST_CASE(test_2) {
  PathWayGraph graph;
  CreateNodes(graph, 5);
  graph.AddEdge(0, 1, 63);
  graph.AddEdge(0, 2, 91);
  graph.AddEdge(0, 3, 40);
  graph.AddEdge(1, 2, 84);
  graph.AddEdge(1, 4, 52);
  graph.AddEdge(2, 3, 32);
  graph.AddEdge(2, 4, 56);
  double ans = 88;
  Dijkstras_algorithm da(graph);
  BOOST_TEST(da.Get_Min_Len() == ans);
}

BOOST_AUTO_TEST_SUITE_END()
