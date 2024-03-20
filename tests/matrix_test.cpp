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

BOOST_AUTO_TEST_SUITE(matrix)

BOOST_AUTO_TEST_CASE(matrix_3x3) {
  AdjacencyMatrix matrix = AdjacencyMatrix(
      {{FLT_MAX, 80, 98}, {91, FLT_MAX, 59}, {16, 21, FLT_MAX}});

  std::pair<float, float> asmt = {155, 205};
  BOOST_TEST(matrix.GetBottomLineEvaluations().first == asmt.first);
  BOOST_TEST(matrix.GetBottomLineEvaluations().second == asmt.second);
}

BOOST_AUTO_TEST_CASE(matrix_4x4) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 36, 35, 91},
                                            {16, FLT_MAX, 31, 92},
                                            {13, 75, FLT_MAX, 63},
                                            {88, 24, 58, FLT_MAX}});

  std::pair<float, float> asmt = {138, 173};
  BOOST_TEST(matrix.GetBottomLineEvaluations().first == asmt.first);
  BOOST_TEST(matrix.GetBottomLineEvaluations().second == asmt.second);
}

BOOST_AUTO_TEST_CASE(matrix_5x5) {
  AdjacencyMatrix matrix = AdjacencyMatrix({{FLT_MAX, 59, 74, 21, 81},
                                            {92, FLT_MAX, 64, 96, 33},
                                            {64, 36, FLT_MAX, 47, 87},
                                            {4, 78, 32, FLT_MAX, 32},
                                            {57, 86, 83, 24, FLT_MAX}});

  std::pair<float, float> asmt = {146, 195};
  BOOST_TEST(matrix.GetBottomLineEvaluations().first == asmt.first);
  BOOST_TEST(matrix.GetBottomLineEvaluations().second == asmt.second);
}

BOOST_AUTO_TEST_SUITE_END()
