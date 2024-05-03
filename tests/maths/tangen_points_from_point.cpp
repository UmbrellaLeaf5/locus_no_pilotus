#include "math/optimal_way/helpers_functions.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_TANGENT_POINTS(const PolygonObstacle& poly, const Point& point,
                          std::pair<std::size_t, std::size_t> indexes) {
  std::vector<Point> vertexes = poly.GetVertexes();
  std::pair<Point, Point> tang_points = TangentPoints(poly, point);
  BOOST_TEST(tang_points.first.x == vertexes[indexes.first].x);
  BOOST_TEST(tang_points.first.y == vertexes[indexes.first].y);
  BOOST_TEST(tang_points.second.x == vertexes[indexes.second].x);
  BOOST_TEST(tang_points.second.y == vertexes[indexes.second].y);
}

BOOST_AUTO_TEST_SUITE(polys_tangent_points, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(poly_3) {
  PolygonObstacle poly({{-5, 0}, {5, 5}, {0, -5}});
  Point point(-10, -2);
  std::pair<std::size_t, std::size_t> indexes{1, 2};
  CHECK_TANGENT_POINTS(poly, point, indexes);
}

BOOST_AUTO_TEST_CASE(poly_4) {
  PolygonObstacle poly({{-10, 10}, {30, 0}, {10, -20}, {-20, 0}});
  Point point(-40, -10);
  std::pair<std::size_t, std::size_t> indexes{0, 2};
  CHECK_TANGENT_POINTS(poly, point, indexes);
}

BOOST_AUTO_TEST_CASE(poly_5) {
  PolygonObstacle poly({{-5, 0}, {-15, 10}, {15, 25}, {25, 15}, {30, -5}});
  Point point(-28.725286, 3.593603);
  std::pair<std::size_t, std::size_t> indexes{0, 2};
  CHECK_TANGENT_POINTS(poly, point, indexes);
}

BOOST_AUTO_TEST_CASE(point_on_poly) {
  PolygonObstacle poly({{-5, 0}, {-15, 10}, {15, 25}, {25, 15}, {30, -5}});
  Point point(-7, 14);
  std::pair<std::size_t, std::size_t> indexes{1, 2};
  CHECK_TANGENT_POINTS(poly, point, indexes);
}

BOOST_AUTO_TEST_CASE(point_is_vertex) {
  PolygonObstacle poly({{-5, 0}, {5, 5}, {0, -5}});
  Point point(0, -5);
  std::pair<std::size_t, std::size_t> indexes{0, 1};
  CHECK_TANGENT_POINTS(poly, point, indexes);
}

BOOST_AUTO_TEST_SUITE_END()
