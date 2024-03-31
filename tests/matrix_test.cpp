#include <QApplication>
#include <cfloat>

#include "../Backend/adjacency_matrix.h"

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(random_matrix)

BOOST_AUTO_TEST_CASE(random_matrix_2x2) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 80}, {91, FLT_MAX}});

  double asmt = 171;
  std::pair<int, int> edge = {1, 2};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(random_matrix_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix(
      {{FLT_MAX, 80, 98}, {91, FLT_MAX, 59}, {16, 21, FLT_MAX}});

  double asmt = 155;
  std::pair<int, int> edge = {2, 3};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(random_matrix_4x4) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 36, 35, 91},
                                            {16, FLT_MAX, 31, 92},
                                            {13, 75, FLT_MAX, 63},
                                            {88, 24, 58, FLT_MAX}});

  double asmt = 138;
  std::pair<int, int> edge = {4, 2};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(random_matrix_5x5) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 59, 74, 21, 81},
                                            {92, FLT_MAX, 64, 96, 33},
                                            {64, 36, FLT_MAX, 47, 87},
                                            {4, 78, 32, FLT_MAX, 32},
                                            {57, 86, 83, 24, FLT_MAX}});

  double asmt = 146;
  std::pair<int, int> edge = {3, 2};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(symmetric_matrix)

BOOST_AUTO_TEST_CASE(symmetric_matrix_4x4) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 18, 99, 64},
                                            {18, FLT_MAX, 81, 25},
                                            {99, 81, FLT_MAX, 55},
                                            {64, 25, 55, FLT_MAX}});

  double asmt = 146;
  std::pair<int, int> edge = {1, 2};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(symmetric_matrix_6x6) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 25, 65, 38, 18, 12},
                                            {25, FLT_MAX, 12, 59, 16, 54},
                                            {65, 12, FLT_MAX, 50, 19, 69},
                                            {38, 59, 50, FLT_MAX, 35, 73},
                                            {18, 16, 19, 35, FLT_MAX, 15},
                                            {12, 54, 69, 73, 15, FLT_MAX}});

  double asmt = 118;
  std::pair<int, int> edge = {2, 3};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(symmetric_matrix_10x10) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix({{FLT_MAX, 21, 188, 268, 461, 131, 366, 449, 492, 62},
                       {21, FLT_MAX, 410, 220, 333, 115, 451, 236, 272, 127},
                       {188, 410, FLT_MAX, 21, 498, 270, 280, 24, 20, 446},
                       {268, 220, 21, FLT_MAX, 48, 382, 492, 119, 414, 330},
                       {461, 333, 498, 48, FLT_MAX, 364, 366, 332, 340, 406},
                       {131, 115, 270, 382, 364, FLT_MAX, 498, 380, 90, 189},
                       {366, 451, 280, 492, 366, 498, FLT_MAX, 477, 105, 379},
                       {449, 236, 24, 119, 332, 380, 477, FLT_MAX, 369, 422},
                       {492, 272, 20, 414, 340, 90, 105, 369, FLT_MAX, 377},
                       {62, 127, 446, 330, 406, 189, 379, 422, 377, FLT_MAX}});

  double asmt = 659;
  std::pair<int, int> edge = {5, 4};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(symm_obstacle_wise_matrix)

BOOST_AUTO_TEST_CASE(symm_obstacle_wise_matrix_4x4) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 18, 99, 64},
                                            {18, FLT_MAX, 81, FLT_MAX},
                                            {99, 81, FLT_MAX, 55},
                                            {64, FLT_MAX, 55, FLT_MAX}});

  double asmt = 146;
  std::pair<int, int> edge = {1, 2};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(symm_obstacle_wise_matrix_6x6) {
  AdjacencyMatrix matrix =
      AdjacencyMatrix({{FLT_MAX, 25, 65, 38, 18, FLT_MAX},
                       {25, FLT_MAX, FLT_MAX, 59, 16, 54},
                       {65, FLT_MAX, FLT_MAX, 50, 19, 69},
                       {38, 59, 50, FLT_MAX, 35, 73},
                       {18, 16, 19, 35, FLT_MAX, 15},
                       {FLT_MAX, 54, 69, 73, 15, FLT_MAX}});

  double asmt = 146;
  std::pair<int, int> edge = {5, 6};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_CASE(symmetric_obstacle_wise_matrix_10x10) {
  AdjacencyMatrix matrix = AdjacencyMatrix(
      {{FLT_MAX, FLT_MAX, FLT_MAX, 268, 461, FLT_MAX, 366, FLT_MAX, 492, 62},
       {FLT_MAX, FLT_MAX, 410, 220, 333, 115, 451, 236, 272, 127},
       {FLT_MAX, 410, FLT_MAX, 21, 498, 270, 280, 24, 20, 446},
       {268, 220, 21, FLT_MAX, 48, 382, 492, 119, FLT_MAX, 330},
       {461, 333, 498, 48, FLT_MAX, 364, 366, FLT_MAX, FLT_MAX, 406},
       {FLT_MAX, 115, 270, 382, 364, FLT_MAX, 498, 380, 90, 189},
       {366, 451, 280, 492, 366, 498, FLT_MAX, 477, 105, 379},
       {FLT_MAX, 236, 24, 119, FLT_MAX, 380, 477, FLT_MAX, 369, 422},
       {492, 272, 20, FLT_MAX, FLT_MAX, 90, 105, 369, FLT_MAX, 377},
       {62, 127, 446, 330, 406, 189, 379, 422, 377, FLT_MAX}});

  double asmt = 708;
  std::pair<int, int> edge = {10, 1};
  BOOST_TEST(matrix.GetBottomLineEvaluation() == asmt);
  BOOST_TEST(matrix.GetSelectedEdge().first == edge.first - 1);
  BOOST_TEST(matrix.GetSelectedEdge().second == edge.second - 1);
}

BOOST_AUTO_TEST_SUITE_END()
