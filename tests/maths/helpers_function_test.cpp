#include <QApplication>

#include "math/optimal_way/helpers_functions.h"
#include "math/optimal_way/obstacles.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;
constexpr double test_precision = 0.00001;

BOOST_AUTO_TEST_SUITE(distance_between_points)

BOOST_AUTO_TEST_CASE(points_on_vertical_line_1) {
  Point point1{1.77, 0.999};
  Point point2{1.77, -0.99999};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 1.99899) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_vertical_line_2) {
  Point point1{-18.2037053, 5.3171399};
  Point point2{-18.2037053, 14.7902559};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 9.473116) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_vertical_line_3) {
  Point point1{3, 10};
  Point point2{3, 14};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 5) < test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_1) {
  Point point1{-9.1023156, -19.7299535};
  Point point2{-9.1023156, -16.2951025};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 3.434851) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_2) {
  Point point1{-1.115817, 5.410206};
  Point point2{-1.115817, 18.344607};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 12.934401) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_3) {
  Point point1{-13, -5};
  Point point2{-13, 8};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 13) < test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_1) {
  Point point1{-9.828609, -18.738824};
  Point point2{-15.800255, -14.964894};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 7.064212) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_2) {
  Point point1{12.086463, 6.295008};
  Point point2{4.557667, -8.741620};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 16.8161514) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_3) {
  Point point1{1.621442, -9.353111};
  Point point2{-19.656616, 1.985277};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 24.110470) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_4) {
  Point point1{1, -91};
  Point point2{-19, 14};
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 106.887791) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(zero_distance) {
  Point point1{5.650934, 8.423567};
  Point point2{5.650934, 8.423567};
  BOOST_TEST(DistanceBetweenPoints(point1, point2) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(distance_between_points_on_circle)

BOOST_AUTO_TEST_CASE(simple_test) {
  Point point1{-10, 0};
  Point point2{10, 0};
  CircleObstacle circle{{0, 0}, 10};
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 31.415926 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_1) {
  Point point1{-5.83, 4.8};
  Point point2{-13.04, 1.28};
  CircleObstacle circle{{7.68, 0.56}, 5.671684};
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 25.28 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_2) {
  Point point1{-7.69, -17.77};
  Point point2{16.67, -11.35};
  CircleObstacle circle{{4.444373, -14.381376}, 12.594773};
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 246.84 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_3) {
  Point point1{14.7, -1.48};
  Point point2{-12.17, 25.75};
  CircleObstacle circle{{-6.157260, 4.806428}, 21.784085};
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 508.41 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(zero_distance) {
  Point point1{14.7, -1.48};
  Point point2{14.7, -1.48};
  CircleObstacle circle{{-6.157260, 4.806428}, 21.784085};
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
