#include <QApplication>
#include <cfloat>

#include "../Backend/adjacency_matrix.h"
#include "../Backend/travelling_salesmans_problem.h"
#include "../Backend/tspgraph.h"

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

void CHECK_PATH(AdjacencyMatrix matrix, std::vector<std::size_t> path) {
  TravellingSalesmansProblem tsp(matrix);
  std::vector<size_t> traj = tsp.GetTrajectory();
  for (std::size_t i = 0; i < path.size(); ++i) {
    BOOST_TEST(path[i] == traj[i]);
  }
}

BOOST_AUTO_TEST_SUITE(suite_1)

BOOST_AUTO_TEST_CASE(case_1) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{FLT_MAX, 59, 74, 21, 81},
                                        {92, FLT_MAX, 64, 96, 33},
                                        {64, 36, FLT_MAX, 47, 87},
                                        {4, 78, 32, FLT_MAX, 32},
                                        {57, 86, 83, 24, FLT_MAX}});
  std::vector<std::size_t> path = {0, 2, 1, 4, 3};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_SUITE_END()
