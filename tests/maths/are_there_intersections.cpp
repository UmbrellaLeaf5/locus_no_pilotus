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

BOOST_AUTO_TEST_CASE(no_intersections_4) {
  PolygonObstacle poly({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  Point p1(-10, 4);
  Point p2(2, 0);
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

BOOST_AUTO_TEST_SUITE(circles)

BOOST_AUTO_TEST_CASE(intersection_1) {
  CircleObstacle circle({0.7, 3.5}, 5.1);
  Point point1(-6.74, 2.32);
  Point point2(1.845, 0);
  BOOST_TEST(AreThereIntersections(circle, point1, point2));
}

BOOST_AUTO_TEST_CASE(intersection_2) {
  CircleObstacle circle({0.7, 3.5}, 5.1);
  Point point1(-6.74, 2.32);
  Point point2(7.02, -1.398);
  BOOST_TEST(AreThereIntersections(circle, point1, point2));
}

BOOST_AUTO_TEST_CASE(no_intersections_1) {
  CircleObstacle circle({6.7, -6.9}, 5.1);
  Point point1(-1.9, -2.075);
  Point point2(4.32, 5.022);
  BOOST_TEST(!AreThereIntersections(circle, point1, point2));
}

BOOST_AUTO_TEST_CASE(semi_intersection) {
  CircleObstacle circle({-3.4, 8.1}, 4.6);
  Point point1(-0.31, 3.561);
  Point point2(-2.704, -9.009);
  BOOST_TEST(!AreThereIntersections(circle, point1, point2));
}

BOOST_AUTO_TEST_CASE(no_intersections_2) {
  CircleObstacle circle({0, 0}, 1);
  Point point1(0, pow(2, 0.5));
  Point point2(-pow(2, 0.5), 0);
  BOOST_TEST(!AreThereIntersections(circle, point1, point2));
}

BOOST_AUTO_TEST_SUITE_END()
