#include "lib/segment.h"

#include <QApplication>
#include <random>

#include "gui/segment.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace lib;

BOOST_AUTO_TEST_SUITE(lib_segment, *utf::tolerance(1.0E-7))

struct {
  Point p_1, p_2, c;
} cases[] = {{{0, 0}, {0, 0}, {0, 0}},
             {{0, -1}, {1, 0}, {0, 0}},
             {{2, 1}, {4, 5}, {3, 3}}},
  exception_cases[] = {{{0, -4211}, {-1, 0}, {-1, 0}},
                       {{0, -1}, {1, 0}, {0, 583}},
                       {{2, 532}, {4, 5}, {3, 3321}}},
  angles_cases[] = {{{1, 0}, {0, 1}, {0, 90}},
                    // angles_case 1:
                    {{(sqrt(3) / 2), (0.5)}, {(0.5), (sqrt(3) / 2)}, {30, 60}},
                    // angles_case 2:
                    {{0.8412862266087, 0.5405899415624},
                     {-0.9798154466877, -0.1999042031378},
                     {32.7238077583897, -168.4686428493179}},
                    // angles_case 3:
                    {{0.8700404619855, 0.4929803185809},
                     {0.3075792827447, -0.9515224562911},
                     {29.5366582168445, -72.0865927712622}},
                    // angles_case 4:
                    {{0.7274022989301, 0.6862112615742},
                     {0.9412391712068, 0.337740762399},
                     {43.3309406164556, 19.7392887461237}},
                    // angles_case 5:
                    {{0.9412391712068, 0.337740762399},
                     {0.7274022989301, 0.6862112615742},
                     {19.7392887461237, 43.3309406164556}},
                    // angles_case 6:
                    {{-0.7695118767117, -0.6386325012084},
                     {0.1849371547577, 0.9827503491681},
                     {-140.310076022729, 79.3425315936843}},

                    {{-0.4542121636543, 0.8908935460472},
                     {0.8944271909999, -0.4472135955},
                     {117.0142549034368, -26.565051177078}}};

// random generator:
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(-1000, 1000);

BOOST_AUTO_TEST_CASE(simple_construct) {
  for (auto c : cases) {
    Segment seg(c.p_1, c.p_2);
    BOOST_CHECK(seg.Start() == c.p_1);
    BOOST_CHECK(seg.End() == c.p_2);
  }
}

BOOST_AUTO_TEST_CASE(circle_construct) {
  for (auto c : cases) {
    Segment seg(c.p_1, c.p_2, c.c);
    BOOST_CHECK(seg.Start() == c.p_1);
    BOOST_CHECK(seg.End() == c.p_2);

    BOOST_CHECK(seg.Center() == c.c);

    BOOST_TEST(seg.Radius() ==
               sqrt(pow(c.c.x - c.p_1.x, 2) + pow(c.c.y - c.p_1.y, 2)));
    BOOST_TEST(seg.Radius() ==
               sqrt(pow(c.c.x - c.p_2.x, 2) + pow(c.c.y - c.p_2.y, 2)));
  }
}

BOOST_AUTO_TEST_CASE(exception_construct) {
  for (auto c : exception_cases) {
    Segment seg(c.p_1, c.p_2);

    BOOST_CHECK(seg.Start() == c.p_1);
    BOOST_CHECK(seg.End() == c.p_2);

    BOOST_CHECK_THROW(Segment s(c.p_1, c.p_2, c.c), std::runtime_error);

    BOOST_CHECK_THROW(seg.Center(), std::runtime_error);
    BOOST_CHECK_THROW(seg.Radius(), std::runtime_error);
  }
}

BOOST_AUTO_TEST_CASE(random_construct) {
  for (int i = 0; i < 1000; i++) {
    Point p_1(dis(gen), dis(gen));
    Point p_2(dis(gen), dis(gen));
    Point c(dis(gen), dis(gen));

    Segment seg(p_1, p_2);
    BOOST_CHECK(seg.Start() == p_1);
    BOOST_CHECK(seg.End() == p_2);

    if (!CouldBeArc(seg, c)) continue;

    Segment arc(p_1, p_2, c);

    BOOST_CHECK(arc.Center() == c);

    BOOST_TEST(arc.Radius() == sqrt(pow(c.x - p_1.x, 2) + pow(c.y - p_1.y, 2)));
    BOOST_TEST(arc.Radius() == sqrt(pow(c.x - p_2.x, 2) + pow(c.y - p_2.y, 2)));
  }
}

BOOST_AUTO_TEST_CASE(angle_test) {
  lib::Point center{0, 0};
  for (auto c : angles_cases) {
    std::pair<double, double> res =
        gui::Segment::GetAngles(c.p_1, c.p_2, center);
    BOOST_TEST(res.first == c.c.x);
    BOOST_TEST(res.second == c.c.y);
  }
}

BOOST_AUTO_TEST_SUITE_END()
