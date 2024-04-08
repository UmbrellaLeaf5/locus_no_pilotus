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

BOOST_AUTO_TEST_SUITE(many_tsp_symmetric)

BOOST_AUTO_TEST_CASE(many_tsp_symmetric_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 661, 18, 637},
                                        {661, inf, 301, 887},
                                        {18, 301, inf, 102},
                                        {637, 887, 102, inf}});
  std::vector<std::size_t> path = {0, 2, 3, 1, 0};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_symmetric_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 259, 42, 145, 475, 47},
                                        {259, inf, 14, 342, 270, 150},
                                        {42, 14, inf, 139, 357, 254},
                                        {145, 342, 139, inf, 32, 256},
                                        {475, 270, 357, 32, inf, 963},
                                        {47, 150, 254, 256, 963, inf}});
  std::vector<std::size_t> path = {0, 2, 1, 4, 3, 0, 5};
  std::size_t num_of_flyers = 2;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_CASE(many_tsp_symmetric_10x10) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 68, 214, 70, 986, 63, 56, 15, 61, 30},
       {68, inf, 856, 14, 980, 119, 642, 637, 47, 518},
       {214, 856, inf, 1093, 247, 899, 441, 824, 1407, 55},
       {70, 14, 1093, inf, 449, 192, 660, 349, 816, 118},
       {986, 980, 247, 449, inf, 12, 920, 791, 43, 546},
       {63, 119, 899, 192, 12, inf, 569, 883, 119, 351},
       {56, 642, 441, 660, 920, 569, inf, 34, 906, 410},
       {15, 637, 824, 349, 791, 883, 34, inf, 573, 446},
       {61, 47, 1407, 816, 43, 119, 906, 573, inf, 98},
       {30, 518, 55, 118, 546, 351, 410, 446, 98, inf}});
  std::vector<std::size_t> path = {0, 2, 9, 0, 6, 7, 0, 5, 4, 8, 1, 3};
  std::size_t num_of_flyers = 3;
  CHECK_PATH(matrix, path, num_of_flyers);
}

BOOST_AUTO_TEST_SUITE_END()
