#include <QApplication>
#include <icecream.hpp>

#include "../backend/dijkstras_algorithm/points_graph.h"

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_1) {
  std::shared_ptr<PointNode> A = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> B = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> S = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> M = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> D = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> R = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> N = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> L = std::make_shared<PointNode>();
  std::shared_ptr<PointNode> G = std::make_shared<PointNode>();
  Edge AB(A, B, 27);
  Edge AM(A, M, 15);
  Edge BL(B, L, 7);
  Edge BG(B, G, 9);
  Edge SM(S, M, 15);
  Edge SD(S, D, 17);
  Edge SG(S, G, 11);
  Edge MD(M, D, 21);
  Edge DR(D, R, 32);
  Edge RN(R, N, 31);
  Edge NL(N, L, 10);
  Edge NG(N, G, 8);
  Dijkstras_algorithm da(A, R);
  double ans = 68;
  BOOST_TEST(da.Get_Min_Len() == ans);
}

BOOST_AUTO_TEST_SUITE_END()
