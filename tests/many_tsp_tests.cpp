#include <QApplication>

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

void CHECK_PATH(AdjacencyMatrix matrix, std::vector<std::size_t> path,
                std::size_t num_of_flyers) {
  TravellingSalesmansProblem tsp(matrix, num_of_flyers);
  std::vector<std::size_t> traj = tsp.GetTrajectory();
  for (std::size_t i = 0; i < path.size(); ++i) {
    BOOST_TEST(path[i] == traj[i]);
  }
}

BOOST_AUTO_TEST_SUITE(many_tsp_random)

BOOST_AUTO_TEST_CASE(many_tsp_random_2x2) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 84}, {20, inf}});
  std::vector<std::size_t> path = {0, 1, 0};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 45, 10}, {90, inf, 145}, {34, 100, inf}});
  std::vector<std::size_t> path = {0, 1, 0, 2};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 661, 104, 637},
                                        {313, inf, 589, 887},
                                        {18, 301, inf, 32},
                                        {37, 866, 102, inf}});
  std::vector<std::size_t> path = {0, 1, 0, 2, 3};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_5x5) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 96, 19, 27, 29},
                                        {95, inf, 772, 560, 284},
                                        {56, 751, inf, 576, 930},
                                        {32, 210, 110, inf, 89},
                                        {80, 743, 600, 84, inf}});
  std::vector<std::size_t> path = {0, 1, 0, 4, 3, 0, 2};
  std::size_t num_of_flyers = 3;
  CHECK_PATH(matrix, path, num_of_flyers);
}
BOOST_AUTO_TEST_SUITE_END()
