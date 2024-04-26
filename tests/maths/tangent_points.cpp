#include <icecream.hpp>

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

LinearFunction MakeOrtagonal(const Point& p1, const Point& p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  Point ort(p2.x + dy, p2.y - dx);
  return LinearFunction(p2, ort);
}

void CHECK_TANGENT_POINTS(
    const PolygonObstacle& poly, const CircleObstacle& circle,
    std::vector<std::pair<std::size_t, Point>>& indexes_and_points) {
  Point center = circle.GetCenter();
  std::vector<Point> v = poly.GetVertexes();
  for (std::size_t i = 0; i < indexes_and_points.size(); ++i) {
    Point p1 = v[indexes_and_points[i].first];
    Point p2 = indexes_and_points[i].second;
    LinearFunction tang =
        (p1 == p2) ? MakeOrtagonal(center, p2) : LinearFunction(p1, p2);
    std::pair<Point, Point> tang_points = TangentPoints(tang, poly, circle);
    BOOST_TEST(tang_points.first.x == p1.x);
    BOOST_TEST(tang_points.first.y == p1.y);
    BOOST_TEST(tang_points.second.x == p2.x);
    BOOST_TEST(tang_points.second.y == p2.y);
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
      {{-14, 0}, {-12, 12}, {-6, 12}, {-4, 10}, {-4, 0}, {-6, -4}, {-12, -2}});
  PolygonObstacle poly2(
      {{0, 4}, {0, 6}, {2, 8}, {4, 8}, {6, 6}, {6, 4}, {4, -4}, {2, -4}});
  std::vector<std::array<std::size_t, 2>> indexes{
      {2, 3}, {3, 7}, {5, 1}, {5, 7}};
  CHECK_TANGENT_POINTS(poly1, poly2, indexes);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(poly_and_circle_tangent_points, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(poly_3_and_circle) {
  PolygonObstacle poly({{-6, 6}, {-4, -2}, {-2, 4}});
  CircleObstacle circle({0, 8}, 2);
  // index of the polys vertex and point on the circle
  std::vector<std::pair<std::size_t, Point>> indexes_and_points{
      {0, {0, 6}}, {0, {-1.2, 9.6}}, {1, {1.686725, 6.925309}}, {2, {-2, 8}}};
  CHECK_TANGENT_POINTS(poly, circle, indexes_and_points);
}

BOOST_AUTO_TEST_CASE(poly_4_and_circle) {
  PolygonObstacle poly({{8, 0}, {12, 2}, {6, 2}, {6, 0}});
  CircleObstacle circle({12, -2}, 4);
  std::vector<std::pair<std::size_t, Point>> indexes_and_points{
      {2, {12, 2}}, {3, {8.620204, -4.139388}}};
  CHECK_TANGENT_POINTS(poly, circle, indexes_and_points);
}

BOOST_AUTO_TEST_CASE(poly_5_and_circle) {
  PolygonObstacle poly({{-14, 0}, {-12, 2}, {-10, -2}, {-10, -4}, {-12, -4}});
  CircleObstacle circle({-12, 10}, 8);
  std::vector<std::pair<std::size_t, Point>> indexes_and_points{
      {1, {-12, 2}}, {3, {-4.829334, 6.452952}}, {4, {-18.565214, 5.428571}}};
  CHECK_TANGENT_POINTS(poly, circle, indexes_and_points);
}

BOOST_AUTO_TEST_CASE(poly_6_and_circle) {
  PolygonObstacle poly(
      {{-8, -4}, {0, -2}, {-4, 2}, {-12, 4}, {-13, 0}, {-12, -3}});
  CircleObstacle circle({5, -5}, sqrt(130));
  std::vector<std::pair<std::size_t, Point>> indexes_and_points{
      {3, {3.323559, 6.277834}}, {5, {-3.536299, -12.558544}}};
  CHECK_TANGENT_POINTS(poly, circle, indexes_and_points);
}

BOOST_AUTO_TEST_CASE(poly_7_and_circle) {
  PolygonObstacle poly(
      {{-14, 0}, {-12, 12}, {-6, 12}, {-4, 10}, {-4, 0}, {-6, -4}, {-12, -2}});
  CircleObstacle circle({0, 20}, sqrt(50));
  std::vector<std::pair<std::size_t, Point>> indexes_and_points{
      {1, {-6.303152, 23.204727}},
      {1, {0.533921, 12.949119}},
      {3, {-6.676347, 17.670539}},
      {5, {6.083551, 16.395779}}};
  CHECK_TANGENT_POINTS(poly, circle, indexes_and_points);
}

BOOST_AUTO_TEST_SUITE_END()
