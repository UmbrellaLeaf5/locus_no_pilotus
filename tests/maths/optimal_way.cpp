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

BOOST_AUTO_TEST_SUITE(polygons, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(one_poly) {
  Point point1(-8.62, 1.33);
  Point point2(3.4752511575043, 6.4339001323606);
  std::vector<CircleObstacle> circles(0);
  std::vector<Point> vertix{{-4.72, 3.65},
                            {-1.84, 2.51},
                            {0, 3.4729910311284},
                            {-0.9088573459776, 5.828631421059},
                            {-1.9558086303911, 6.5484104290933},
                            {-3.6, 6.19},
                            {-4.78, 4.95}};
  std::vector<PolygonObstacle> polys{{vertix}};
  double correct_length = 13.5242447275625;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}

BOOST_AUTO_TEST_CASE(two_polys) {
  Point point1(-8.88, 5.55);
  Point point2(10.84, -3.23);
  std::vector<CircleObstacle> circles(0);
  std::vector<Point> vertix1{{-5.82, 5.93}, {-6.54, 4.27}, {-4.94, 0.47},
                             {-1.14, 2.11}, {-1.7, 4.55},  {-2.88, 6.17},
                             {-4.54, 6.51}};
  std::vector<Point> vertix2{{3.38, -0.11}, {3.56, 1.85},  {4.8, 2.79},
                             {8.92, 2.55},  {5.66, -1.73}, {3.84, -1.33}};
  std::vector<PolygonObstacle> polys{{vertix1}, {vertix2}};
  double correct_length = 22.6368146106518;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}

BOOST_AUTO_TEST_CASE(two_polys_2) {
  Point point1(16.0867119995807, 81.82110410565608);
  Point point2(-26.39655465103465, -5.341297839758592);
  std::vector<CircleObstacle> circles(0);
  std::vector<Point> vertix1{{-21.9547, 12.0331},
                             {-25.1369, 5.28401},
                             {-13.7517, 4.58098},
                             {-14.3881, 10.9082}};
  std::vector<Point> vertix2{{23.426576955006283, 77.79346124390177},
                             {38.245488935037955, 60.2493893479525},
                             {28.936172434761644, 43.479320623883325},
                             {12.977344148573707, 51.9933555145646},
                             {7.087776566766259, 72.89144115532771}};
  std::vector<PolygonObstacle> polys{{vertix1}, {vertix2}};
  double correct_length = 98.2718720490988;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}

BOOST_AUTO_TEST_CASE(three_polys) {
  Point point1(-10.8878429725857, -8.4678597369649);
  Point point2(20.3621535335072, 11.5873162890166);
  std::vector<CircleObstacle> circles(0);
  std::vector<Point> vertix1{{4.710627269844334, -11.067604777369938},
                             {-10.834786951352983, 0.39249580890520747},
                             {-3.3008319363017242, 8.669235121215035},
                             {6.726756076689037, 8.8284031849133},
                             {7.734820480111389, 3.5228010616377703},
                             {7.8409325225768995, -1.3583528917757175},
                             {7.416484352714857, -4.913106314370323},
                             {6.35536392805975, -9.369812097921768},
                             {5.718691673266686, -10.59010058627514}};
  std::vector<Point> vertix2{{11.0242937965422, -1.1991848280775},
                             {10.2815094992836, 3.3636329979395},
                             {11.7670780938008, 7.1306105054651},
                             {14.8443273253006, 8.669235121215},
                             {16.6482320472143, 5.857265995879},
                             {16.6482320472143, 2.6739047219137},
                             {15, 0},
                             {13.570982815714478, -1.7828010616377599}};
  std::vector<Point> vertix3{{21.6354980430933, -10.0595403739476},
                             {16.6482320472143, -2.7908654650601},
                             {3.8086749088875, -14.7284702424301}};
  std::vector<PolygonObstacle> polys{{vertix1}, {vertix2}, {vertix3}};
  double correct_length = 43.8106387108272;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}

BOOST_AUTO_TEST_CASE(weird_poly) {
  Point point1(5, -3);
  Point point2(0.8, 4.29);
  std::vector<CircleObstacle> circles(0);
  std::vector<Point> vertix1{{-1.66, -1.39}, {3.26, 4.67}};
  std::vector<PolygonObstacle> polys{{vertix1}};
  double correct_length = 10.3540669068468;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circles_and_polys, *utf::tolerance(1.0E-5))
BOOST_AUTO_TEST_CASE(one_poly_one_circle) {
  Point point1(10.88, 3.65);
  Point point2(2.04, 3.19);
  std::vector<CircleObstacle> circles{{{4.18, 2.97}, 1.33}};
  std::vector<Point> vertix{{6.96, 1.75}, {6.24, 3.59}, {6.4, 5.69},
                            {7.8, 6.65},  {9.48, 5.31}, {10.52, 2.71},
                            {9.88, 1.81}, {8.02, 0.69}};
  std::vector<PolygonObstacle> polys{{vertix}};
  double correct_length = 10.9484801817353;
  CHECK_OPTIMAL_WAY(point1, point2, correct_length, circles, polys);
}
BOOST_AUTO_TEST_SUITE_END()
