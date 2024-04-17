#include <QApplication>
#include <cfloat>

#include "math/littles_algorithm/adjacency_matrix.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_MATRIX(AdjacencyMatrix matrix, double asmt,
                  std::pair<int, int> edge) {
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second);
}

BOOST_AUTO_TEST_SUITE(random_matrix)

BOOST_AUTO_TEST_CASE(random_matrix_2x2) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 80}, {91, inf}});

  double asmt = 171;
  std::pair<int, int> edge = {0, 1};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(random_matrix_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix::WithExtraRowCol(
      {{inf, 80, 98}, {91, inf, 59}, {16, 21, inf}});

  double asmt = 155;
  std::pair<int, int> edge = {1, 2};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(random_matrix_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 36, 35, 91},
                                        {16, inf, 31, 92},
                                        {13, 75, inf, 63},
                                        {88, 24, 58, inf}});

  double asmt = 138;
  std::pair<int, int> edge = {3, 1};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(random_matrix_5x5) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 59, 74, 21, 81},
                                        {92, inf, 64, 96, 33},
                                        {64, 36, inf, 47, 87},
                                        {4, 78, 32, inf, 32},
                                        {57, 86, 83, 24, inf}});

  double asmt = 146;
  std::pair<int, int> edge = {2, 1};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(symmetric_matrix)

BOOST_AUTO_TEST_CASE(symmetric_matrix_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 18, 99, 64},
                                        {18, inf, 81, 25},
                                        {99, 81, inf, 55},
                                        {64, 25, 55, inf}});

  double asmt = 146;
  std::pair<int, int> edge = {0, 1};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(symmetric_matrix_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 25, 65, 38, 18, 12},
                                        {25, inf, 12, 59, 16, 54},
                                        {65, 12, inf, 50, 19, 69},
                                        {38, 59, 50, inf, 35, 73},
                                        {18, 16, 19, 35, inf, 15},
                                        {12, 54, 69, 73, 15, inf}});

  double asmt = 118;
  std::pair<int, int> edge = {1, 2};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(symmetric_matrix_10x10) {
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

  double asmt = 659;
  std::pair<int, int> edge = {4, 3};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(symm_obstacle_wise_matrix)

BOOST_AUTO_TEST_CASE(symm_obstacle_wise_matrix_4x4) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 18, 99, 64},
                                        {18, inf, 81, inf},
                                        {99, 81, inf, 55},
                                        {64, inf, 55, inf}});

  double asmt = 146;
  std::pair<int, int> edge = {0, 1};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(symm_obstacle_wise_matrix_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix::WithExtraRowCol({{inf, 25, 65, 38, 18, inf},
                                        {25, inf, inf, 59, 16, 54},
                                        {65, inf, inf, 50, 19, 69},
                                        {38, 59, 50, inf, 35, 73},
                                        {18, 16, 19, 35, inf, 15},
                                        {inf, 54, 69, 73, 15, inf}});

  double asmt = 146;
  std::pair<int, int> edge = {4, 5};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_CASE(symmetric_obstacle_wise_matrix_10x10) {
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

  double asmt = 708;
  std::pair<int, int> edge = {9, 0};
  CHECK_MATRIX(matrix, asmt, edge);
}

BOOST_AUTO_TEST_SUITE_END()
