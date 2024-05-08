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
                       {{2, 532}, {4, 5}, {3, 3321}}};

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

BOOST_AUTO_TEST_SUITE_END()
