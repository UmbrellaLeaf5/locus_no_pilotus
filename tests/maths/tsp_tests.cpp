#include <QApplication>
#include <algorithm>

#include "math/littles_algorithm/adjacency_matrix.h"
#include "math/littles_algorithm/travelling_salesmans_problem.h"
#include "math/littles_algorithm/tspgraph.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_PATH(AdjacencyMatrix matrix, std::vector<std::size_t> path) {
  double len = 0;
  for (std::size_t i = 0; i < path.size() - 1; ++i)
    len += matrix.GetMatrixValue(path[i], path[i + 1]);
  len += matrix.GetMatrixValue(path[path.size() - 1], 0);

  TravellingSalesmansProblem tsp(matrix);
  std::vector<std::size_t> traj = tsp.GetTrajectory();
  double traj_len = tsp.GetTrajLength();

  for (std::size_t i = 0; i < traj.size(); ++i) {
    bool is_found = (std::find(traj.begin(), traj.end(), i) != traj.end());
    BOOST_TEST(is_found);
  }
  BOOST_TEST(path.size() == traj.size());
  BOOST_TEST(len == traj_len);
}

BOOST_AUTO_TEST_SUITE(tsp_random)

BOOST_AUTO_TEST_CASE(tsp_random_2x2) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 80}, {91, inf}});
  std::vector<std::size_t> path = {0, 1};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_random_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 80, 98}, {91, inf, 59}, {16, 21, inf}});
  std::vector<std::size_t> path = {0, 1, 2};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_random_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 36, 35, 91},
                                        {16, inf, 31, 92},
                                        {13, 75, inf, 63},
                                        {88, 24, 58, inf}});
  std::vector<std::size_t> path = {0, 2, 3, 1};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_random_5x5) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 59, 74, 21, 81},
                                        {92, inf, 64, 96, 33},
                                        {64, 36, inf, 47, 87},
                                        {4, 78, 32, inf, 32},
                                        {57, 86, 83, 24, inf}});
  std::vector<std::size_t> path = {0, 2, 1, 4, 3};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tsp_symmetric)

BOOST_AUTO_TEST_CASE(tsp_symmetric_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 18, 99, 64},
                                        {18, inf, 81, 25},
                                        {99, 81, inf, 55},
                                        {64, 25, 55, inf}});
  std::vector<std::size_t> path = {0, 2, 3, 1};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_symmetric_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 25, 65, 38, 18, 12},
                                        {25, inf, 12, 59, 16, 54},
                                        {65, 12, inf, 50, 19, 69},
                                        {38, 59, 50, inf, 35, 73},
                                        {18, 16, 19, 35, inf, 15},
                                        {12, 54, 69, 73, 15, inf}});
  std::vector<std::size_t> path = {0, 5, 4, 1, 2, 3};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_symmetric_10x10) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 21, 188, 268, 461, 131, 366, 449, 492, 62},
       {21, inf, 410, 220, 333, 115, 451, 236, 272, 127},
       {188, 410, inf, 21, 498, 270, 280, 24, 20, 446},
       {268, 220, 21, inf, 48, 382, 492, 119, 414, 330},
       {461, 333, 498, 48, inf, 364, 366, 332, 340, 406},
       {131, 115, 270, 382, 364, inf, 498, 380, 90, 189},
       {366, 451, 280, 492, 366, 498, inf, 477, 105, 379},
       {449, 236, 24, 119, 332, 380, 477, inf, 369, 422},
       {492, 272, 20, 414, 340, 90, 105, 369, inf, 377},
       {62, 127, 446, 330, 406, 189, 379, 422, 377, inf}});
  std::vector<std::size_t> path = {0, 1, 7, 2, 3, 4, 6, 8, 5, 9};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tsp_symm_obstacle_wise)

BOOST_AUTO_TEST_CASE(tsp_symm_obstacle_wise_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 18, 99, 64},
                                        {18, inf, 81, inf},
                                        {99, 81, inf, 55},
                                        {64, inf, 55, inf}});
  std::vector<std::size_t> path = {0, 1, 2, 3};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_symm_obstacle_wise_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 25, 65, 38, 18, inf},
                                        {25, inf, inf, 59, 16, 54},
                                        {65, inf, inf, 50, 19, 69},
                                        {38, 59, 50, inf, 35, 73},
                                        {18, 16, 19, 35, inf, 15},
                                        {inf, 54, 69, 73, 15, inf}});
  std::vector<std::size_t> path = {0, 3, 2, 4, 5, 1};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_CASE(tsp_symm_obstacle_wise_10x10) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, inf, inf, 268, 461, inf, 366, inf, 492, 62},
       {inf, inf, 410, 220, 333, 115, 451, 236, 272, 127},
       {inf, 410, inf, 21, 498, 270, 280, 24, 20, 446},
       {268, 220, 21, inf, 48, 382, 492, 119, inf, 330},
       {461, 333, 498, 48, inf, 364, 366, inf, inf, 406},
       {inf, 115, 270, 382, 364, inf, 498, 380, 90, 189},
       {366, 451, 280, 492, 366, 498, inf, 477, 105, 379},
       {inf, 236, 24, 119, inf, 380, 477, inf, 369, 422},
       {492, 272, 20, inf, inf, 90, 105, 369, inf, 377},
       {62, 127, 446, 330, 406, 189, 379, 422, 377, inf}});
  std::vector<std::size_t> path = {0, 6, 4, 3, 7, 2, 8, 5, 1, 9};
  CHECK_PATH(matrix, path);
}

BOOST_AUTO_TEST_SUITE_END()
