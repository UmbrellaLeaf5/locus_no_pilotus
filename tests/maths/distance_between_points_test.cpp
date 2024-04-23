#include "math/optimal_way/helpers_functions.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;
constexpr double test_precision = 0.00001;

void CHECK_DISTANCES(const PolygonObstacle& poly,
                     const std::vector<double>& dist) {
  std::vector<Point> vertexes = poly.GetVertexes();
  std::size_t n = poly.GetVertexes().size();
  std::size_t count = 0;
  BOOST_TEST(dist.size() == n * (n - 1) / 2);
  for (std::size_t i = 0; i < n - 1; ++i)
    for (std::size_t j = i + 1; j < n; ++j) {
      BOOST_TEST(
          DistanceBetweenPointsOnPolygon(poly, vertexes[i], vertexes[j]) -
              dist[count] <
          test_precision);
      ++count;
    }
}

BOOST_AUTO_TEST_SUITE(distance_between_points)

BOOST_AUTO_TEST_CASE(points_on_vertical_line_1) {
  Point point1(1.77, 0.999);
  Point point2(1.77, -0.99999);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 1.99899) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_vertical_line_2) {
  Point point1(-18.2037053, 5.3171399);
  Point point2(-18.2037053, 14.7902559);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 9.473116) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_vertical_line_3) {
  Point point1(3, 10);
  Point point2(3, 14);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 4) < test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_1) {
  Point point1(-9.1023156, -19.7299535);
  Point point2(-9.1023156, -16.2951025);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 3.434851) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_2) {
  Point point1(-1.115817, 5.410206);
  Point point2(-1.115817, 18.344607);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 12.934401) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_horizontal_line_3) {
  Point point1(-13, -5);
  Point point2(-13, 8);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 13) < test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_1) {
  Point point1(-9.828609, -18.738824);
  Point point2(-15.800255, -14.964894);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 7.064212) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_2) {
  Point point1(12.086463, 6.295008);
  Point point2(4.557667, -8.741620);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 16.8161514) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_3) {
  Point point1(1.621442, -9.353111);
  Point point2(-19.656616, 1.985277);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 24.110470) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(points_on_random_line_4) {
  Point point1(1, -91);
  Point point2(-19, 14);
  BOOST_TEST((DistanceBetweenPoints(point1, point2) - 106.887791) <
             test_precision);
}

BOOST_AUTO_TEST_CASE(zero_distance) {
  Point point1(5.650934, 8.423567);
  Point point2(5.650934, 8.423567);
  BOOST_TEST(DistanceBetweenPoints(point1, point2) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(distance_between_points_on_circle)

BOOST_AUTO_TEST_CASE(simple_test) {
  Point point1(-10, 0);
  Point point2(10, 0);
  CircleObstacle circle({0, 0}, 10);
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 31.415926 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_1) {
  Point point1(5.83, -4.8);
  Point point2(13.041218, -1.286467);
  CircleObstacle circle({7.68, 0.56}, 5.670282);
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 8.910595 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_2) {
  Point point1(-7.69, -17.77);
  Point point2(16.670395, -11.339995);
  CircleObstacle circle({4.444373, -14.381376}, 12.598639);
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 39.220643 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(random_points_and_circle_3) {
  Point point1(14.7, -1.48);
  Point point2(-12.173166, 25.743317);
  CircleObstacle circle({-6.157260, 4.806428}, 21.784041);
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) - 46.690539 <
             test_precision);
}

BOOST_AUTO_TEST_CASE(zero_distance) {
  Point point1(14.7, -1.48);
  Point point2(14.7, -1.48);
  CircleObstacle circle({-6.157260, 4.806428}, 21.784041);
  BOOST_TEST(DistanceBetweenPointsOnCircle(circle, point1, point2) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(distance_between_points_on_polygon)

BOOST_AUTO_TEST_CASE(line) {
  PolygonObstacle poly({{0, 30}, {24, 10}});
  std::vector<double> dist{31.240998};
  CHECK_DISTANCES(poly, dist);
}

BOOST_AUTO_TEST_CASE(triangle) {
  PolygonObstacle poly({{0, 0}, {4, 4}, {6, -2}});
  std::vector<double> dist{5.656854, 6.324555, 6.324555};
  CHECK_DISTANCES(poly, dist);
}

BOOST_AUTO_TEST_CASE(quadrangle) {
  PolygonObstacle poly({{-4, 0}, {0, 10}, {8, 0}, {4, -6}});
  std::vector<double> dist{10.770329, 17.211102, 10,
                           12.806248, 20.017351, 7.211102};
  CHECK_DISTANCES(poly, dist);
}

BOOST_AUTO_TEST_CASE(pentagon) {
  PolygonObstacle poly({{-5, 0}, {0, -10}, {20, 0}, {15, 15}, {0, 15}});
  std::vector<double> dist{11.180339, 33.541019, 30.811388, 15.811388,
                           22.360679, 38.172068, 26.991728, 15.811388,
                           30.811388, 15};
  CHECK_DISTANCES(poly, dist);
}

BOOST_AUTO_TEST_CASE(hexagon) {
  PolygonObstacle poly(
      {{43, 58}, {48, 57}, {51, 58}, {52, 60}, {47, 63}, {43, 60}});
  std::vector<double> dist{5.099019, 8.261297,  10.497365, 7,         2,
                           3.162277, 5.398345,  11.229297, 7.099019,  2.236067,
                           8.067019, 10.261297, 5.830951,  10.830951, 5};
  CHECK_DISTANCES(poly, dist);
}

BOOST_AUTO_TEST_SUITE_END()
