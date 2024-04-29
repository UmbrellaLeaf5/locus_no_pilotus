#include "math/optimal_way/helpers_functions.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace math;

void CHECK_TANGENTS(std::vector<LinearFunction> func_tangents,
                    std::vector<LinearFunction> correct_tangents) {
  std::size_t amount_of_matches = 0;
  BOOST_TEST(func_tangents.size() == correct_tangents.size());
  for (std::size_t i = 0; i < func_tangents.size(); ++i)
    for (std::size_t j = 0; j < correct_tangents.size(); ++j)
      if (func_tangents[i] == correct_tangents[j]) amount_of_matches += 1;
  BOOST_TEST(amount_of_matches == correct_tangents.size());
}

BOOST_AUTO_TEST_SUITE(tangents_between_two_circles, *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(random_circles_1) {
  CircleObstacle circle1({-10, 1.6}, 3);
  CircleObstacle circle2({3.9, -6.24}, 3);
  std::vector<LinearFunction> tangents = TangentsBetween(circle1, circle2);
  std::vector<LinearFunction> correct_tangents{
      {0.491272431455, 0.871005969034, 6.5191147641},
      {0.127752494027, 0.991806079972, 2.69063521232},
      {0.782703341301, 0.622394954603, 3.83120148565},
      {0.491272431455, 0.871005969034, 0.519114764096}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(random_circles_2) {
  CircleObstacle circle1({17.491289, 7.633909}, 13.698395);
  CircleObstacle circle2({-1.203626, 14.719739}, 2.955452);
  std::vector<LinearFunction> tangents = TangentsBetween(circle1, circle2);
  std::vector<LinearFunction> correct_tangents{
      {0.801367255451, 0.598172652243, -4.88494685374},
      {0.975016282663, 0.22213340258, -5.05164276092},
      {-0.582828968081, 0.812594852289, -9.70724023797},
      {-0.203556275524, 0.979063247546, -17.612013094}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(random_circles_3) {
  CircleObstacle circle1({-11.026499, 22.804150}, 17.464188);
  CircleObstacle circle2({19.615980, 29.060269}, 13.149828);
  std::vector<LinearFunction> tangents = TangentsBetween(circle1, circle2);
  std::vector<LinearFunction> correct_tangents{
      {-0.333288465128, 0.942824903687, -7.71113745486},
      {-0.999989874802, 0.00450003250376, 6.33518122926},
      {0.918196037558, 0.396126288717, -16.3730236169},
      {-0.0629631156917, 0.998015854615, -40.9173539832}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(circles_intersect) {
  CircleObstacle circle1({-11.026499, 22.804150}, 17.464188);
  CircleObstacle circle2({5.794354, 29.12345}, 3.16453);
  std::vector<LinearFunction> tangents = TangentsBetween(circle1, circle2);
  std::vector<LinearFunction> correct_tangents{
      {-0.957932892447, 0.286992288342, 0.356926727171},
      {0.532010319606, 0.846737869611, -30.9071141322}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(circles_touch) {
  CircleObstacle circle1({0, 0}, 2);
  CircleObstacle circle2({3, 4}, 3);
  std::vector<LinearFunction> tangents = TangentsBetween(circle1, circle2);
  std::vector<LinearFunction> correct_tangents{
      {-0.663836717691, 0.747877538268, 2},
      {0.6, 0.8, -2},
      {-0.903836717691, 0.427877538268, -2}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tangents_between_poly_and_circles,
                      *utf::tolerance(1.0E-5))

BOOST_AUTO_TEST_CASE(random_poly_and_circle_1) {
  PolygonObstacle poly({{-6, 6}, {-4, -2}, {-2, 4}});
  CircleObstacle circle({2, 6}, 2);
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {1.9364917, 7.5, -33.38105},
      {-1.9364917, 7.5, -56.61895},
      {-6.504245, 7.327673, -11.361633},
      {-8.855755, 4.192326, -27.0383672}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(random_poly_and_circle_2) {
  PolygonObstacle poly({{-10, 4}, {-8, -2}, {0, -2}, {-4, 2}});
  CircleObstacle circle({3, 5}, 4);
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {2.8900178, 12.0684629, -19.3736734},
      {-4.7017825, 11.4844782, -92.9557383},
      {-3.7281226, 5.3010472, 10.6020944},
      {-6.4098084, -0.9562196, -1.9124392}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(random_poly_and_circle_3) {
  PolygonObstacle poly(
      {{-14, 0}, {-12, 12}, {-6, 12}, {-4, 10}, {-4, 0}, {-6, -4}, {-12, -2}});
  CircleObstacle circle({2, -2}, 5);
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {10.2954292, 11.3579987, -74.5234095},
      {12.4083165, 1.0167001, 39.4662650},
      {-5.1220226, 4.0944943, -14.3541586},
      {4.6702489, 12.2142857, 80.4715578}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(poly_and_circle_touch) {
  PolygonObstacle poly(
      {{-14, 0}, {-12, 12}, {-6, 12}, {-4, 10}, {-4, 0}, {-6, -4}, {-12, -2}});
  CircleObstacle circle({0, 5}, 4);
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {3.3369532622349, 7.606887860726, -71.2609347553021},
      {-5.7077178213085, 8.2717566013705, -1.1592805223691},
      {1, 0, 4}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(poly_and_circle_intersect_1) {
  PolygonObstacle poly(
      {{0, 4}, {0, 6}, {2, 8}, {4, 8}, {6, 6}, {6, 4}, {4, -4}, {2, -4}});
  CircleObstacle circle({3, 5}, 5);
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {1.9478821740147, 1, 0.1042356519705},
      {-1.9478821740147, 1, 11.791528696059}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_CASE(poly_and_circle_intersect_2) {
  PolygonObstacle poly(
      {{0, 4}, {0, 6}, {2, 8}, {4, 8}, {6, 6}, {6, 4}, {4, -4}, {2, -4}});
  CircleObstacle circle({3, 5}, sqrt(10));
  std::vector<LinearFunction> tangents =
      TangentsBetween<CircleObstacle>(poly, circle);
  std::vector<LinearFunction> correct_tangents{
      {3.9814239699997, -1, -19.9256958799989},
      {3.9814239699997, 1, -3.9628479399994}};
  CHECK_TANGENTS(tangents, correct_tangents);
}

BOOST_AUTO_TEST_SUITE_END()
