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
  std::vector<size_t> traj = tsp.GetTrajectory();
  for (std::size_t i = 0; i < path.size(); ++i) {
    BOOST_TEST(path[i] == traj[i]);
  }
}

BOOST_AUTO_TEST_SUITE(many_tsp_random)

BOOST_AUTO_TEST_CASE(many_tsp_random_2x2) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 84}, {20, inf}});
  std::vector<std::size_t> path = {0, 1, 2};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 45, 10}, {90, inf, 145}, {34, 100, inf}});
  std::vector<std::size_t> path = {0, 1, 3, 2};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 661, 104, 637},
                                        {313, inf, 589, 887},
                                        {18, 301, inf, 32},
                                        {37, 866, 102, inf}});
  std::vector<std::size_t> path = {0, 1, 4, 2, 3};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_random_5x5) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 967, 19, 27, 290},
                                        {95, inf, 772, 56, 284},
                                        {56, 751, inf, 576, 93},
                                        {324, 210, 11, inf, 894},
                                        {80, 743, 60, 847, inf}});
  std::vector<std::size_t> path = {0, 2, 4, 5, 3, 1};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}
BOOST_AUTO_TEST_SUITE_END()
