#include "math/optimal_way/optimal_way.h"

#include <vector>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_OPTIMAL_WAY(
    Point point1, Point point2, double correct_length,
    std::vector<CircleObstacle> circles = std::vector<CircleObstacle>(0),
    std::vector<PolygonObstacle> polys = std::vector<PolygonObstacle>(0)) {
  OptimalWayCalculator optimal_way(circles, polys);
  optimal_way.FindOptimalWay(point1, point2);
  BOOST_TEST(optimal_way.GetOptimalWayLength() == correct_length);
}

BOOST_AUTO_TEST_SUITE(circles, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(no_obstacle) {
  Point point1(-4, -2);
  Point point2(2, 2);
  double correct_length = 7.211102550928;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length);
}

BOOST_AUTO_TEST_CASE(no_intersection_with_obstacle) {
  Point point1(-4, -2);
  Point point2(2, 2);
  std::vector<CircleObstacle> circles{
      {{-6, 3.63}, 3.14}, {{0, 6}, 2}, {{0.52, -2.29}, 2.67}};
  double correct_length = 7.211102550928;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(one_circle) {
  Point point1(-14.0132039928426, 7.1795675700574);
  Point point2(-2, 12);
  std::vector<CircleObstacle> circles{
      {{-7.3068822623426, 10.6983241111571}, 3.78}};
  double correct_length = 14.4541288041882;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(two_circles_1) {
  Point point1(-7.98, 1.23);
  Point point2(8.16, 2.27);
  std::vector<CircleObstacle> circles{{{-6.44, 3.95}, 2.4186773244896},
                                      {{0.32, 1.17}, 4.1780856860529}};
  double correct_length = 18.0308833947264;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(two_circles_2) {
  Point point1(2.8860028860028857, 3.02);
  Point point2(0.6854256854256855, 3.15);
  std::vector<CircleObstacle> circles{
      {{2.2005772005772006, 3.43}, 0.5398077722761565},
      {{0.9090909090909092, 2.3400000000000003}, 0.6977516532510056}};
  double correct_length = 2.2359987212926;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(three_circles) {
  Point point1(-7.38, 4.09);
  Point point2(7.44, -1.99);
  std::vector<CircleObstacle> circles{{{-4.28, 1.05}, 2.4681166909204},
                                      {{-0.72, 3.67}, 1.6430459518833},
                                      {{3.36, -0.07}, 2.3610379073619}};
  double correct_length = 17.2452972633048;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(many_circles) {
  Point point1(-8, 4);
  Point point2(14.9201948893853, -3.6843177290538);
  std::vector<CircleObstacle> circles{
      {{-5.99, -0.544}, 0.682641926635}, {{-1.1, -0.648}, 2.7261826791321},
      {{2.508, 2.434}, 1.067771511139},  {{3.406, -0.52}, 1.308214049764},
      {{5.43, 0.646}, 0.8281473298876},  {{7.056, -1.736}, 1.46175374123}};
  double correct_length = 24.3588408767565;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_CASE(many_circles_2) {
  Point point1(3.10967, 3.27);
  Point point2(1.29149, 0.84);
  std::vector<CircleObstacle> circles{
      {{1.6233766233766234, 2.44}, 0.6374372349316524},
      {{0.3463203463203463, 3.54}, 0.40295210083288274},
      {{2.647907647907648, 3.84}, 0.32875169441430113},
      {{1.9336219336219338, 1.03}, 0.5693287325398032},
      {{1.5007215007215007, 4.59}, 0.3984371374874696},
      {{3.5714285714285716, 3.5}, 0.19135454700142618},
      {{3.5642135642135644, 4.48}, 0.31775186959715124},
      {{3.2323232323232327, 2.66}, 0.4448578559741175},
      {{2.676767676767677, 1.96}, 0.2645089838359704}};
  double correct_length = 3.0726744815740017;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles);
}

BOOST_AUTO_TEST_SUITE_END()
