#include "math/optimal_way/helpers_functions.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_TANGENT_POINTS(const PolygonObstacle& poly1,
                          const PolygonObstacle& poly2,
                          std::vector<std::array<std::size_t, 2>>& indexes) {
  std::vector<Point> v1 = poly1.GetVertexes();
  std::vector<Point> v2 = poly2.GetVertexes();
  for (std::size_t i = 0; i < 4; ++i) {
    LinearFunction tang(v1[indexes[i][0]], v2[indexes[i][1]]);
    std::pair<Point, Point> tang_points = TangentPoints(tang, poly1, poly2);
    BOOST_TEST(tang_points.first.x == v1[indexes[i][0]].x);
    BOOST_TEST(tang_points.first.y == v1[indexes[i][0]].y);
    BOOST_TEST(tang_points.second.x == v2[indexes[i][1]].x);
    BOOST_TEST(tang_points.second.y == v2[indexes[i][1]].y);
  }
}

BOOST_AUTO_TEST_SUITE(polys_tangent_points, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(polys_3x3) {
  PolygonObstacle poly1({{-6, 6}, {-4, -2}, {-2, 4}});
  PolygonObstacle poly2({{2, 0}, {4, 2}, {6, -2}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {0, 1}, {1, 1}, {1, 2}, {2, 0}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_CASE(polys_3x4) {
  PolygonObstacle poly1({{-6, 6}, {-4, 4}, {4, 2}});
  PolygonObstacle poly2({{8, 0}, {12, 2}, {6, 2}, {6, 0}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {0, 1}, {1, 3}, {2, 2}, {2, 3}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_CASE(polys_4x5) {
  PolygonObstacle poly1({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  PolygonObstacle poly2({{0, 2}, {2, 0}, {4, 2}, {2, 4}, {0, 4}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {0, 4}, {2, 3}, {2, 4}, {3, 1}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_CASE(polys_5x5) {
  PolygonObstacle poly1({{-14, 0}, {-12, 2}, {-10, -2}, {-10, -4}, {-12, -4}});
  PolygonObstacle poly2({{-8, -2}, {0, -4}, {-4, 2}, {-12, 4}, {-10, 0}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {0, 3}, {1, 4}, {2, 3}, {4, 1}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_CASE(polys_7x8) {
  PolygonObstacle poly1(
      {{-14, 0}, {12, 12}, {-6, 12}, {-4, 10}, {-4, 0}, {-6, -4}, {-12, -2}});
  PolygonObstacle poly2(
      {{0, 4}, {0, 6}, {2, 8}, {4, 8}, {6, 6}, {6, 4}, {4, -4}, {2, -4}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {2, 3}, {3, 7}, {5, 1}, {5, 7}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_SUITE_END()
