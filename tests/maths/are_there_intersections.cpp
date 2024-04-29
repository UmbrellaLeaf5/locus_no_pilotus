#include "math/optimal_way/helpers_functions.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

BOOST_AUTO_TEST_SUITE(polys)

BOOST_AUTO_TEST_CASE(no_intersections_1) {
  PolygonObstacle poly({{-6, 6}, {-4, -2}, {-2, 4}});
  Point p1(-2, -2);
  Point p2(-1, 6);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == false);
}

BOOST_AUTO_TEST_CASE(no_intersections_2) {
  PolygonObstacle poly({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  Point p1(-3.8, 2);
  Point p2(3.8, -6);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == false);
}

BOOST_AUTO_TEST_CASE(no_intersections_3) {
  PolygonObstacle poly({{-8, -2}, {0, -4}, {-4, 2}, {-12, 4}, {-10, 0}});
  Point p1(0, 2);
  Point p2(-12, 4);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == false);
}

BOOST_AUTO_TEST_CASE(semi_intersection_1) {
  PolygonObstacle poly({{-6, 6}, {-4, -2}, {-2, 4}});
  Point p1(-2, -2);
  Point p2(-1, -6);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_CASE(semi_intersections_2) {
  PolygonObstacle poly({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  Point p1(-3.8, 2);
  Point p2(-3.8, 3);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_CASE(semi_intersections_3) {
  PolygonObstacle poly({{-8, -2}, {0, -4}, {-4, 2}, {-12, 4}, {-10, 0}});
  Point p1(0, 2);
  Point p2(-2, 1);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == false);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_CASE(intersection_1) {
  PolygonObstacle poly({{-6, 6}, {-4, -2}, {-2, 4}});
  Point p1(-2, -2);
  Point p2(-6, 8);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == true);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_CASE(intersection_2) {
  PolygonObstacle poly({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  Point p1(0, 6);
  Point p2(-12, -6);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == true);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_CASE(intersection_3) {
  PolygonObstacle poly({{-8, -2}, {0, -4}, {-4, 2}, {-12, 4}, {-10, 0}});
  Point p1(2, 4);
  Point p2(-16, -2);
  BOOST_TEST(AreThereIntersections(poly, p1, p2) == true);
  BOOST_TEST(AreThereIntersections(poly, LinearFunction(p1, p2)) == true);
}

BOOST_AUTO_TEST_SUITE_END()
