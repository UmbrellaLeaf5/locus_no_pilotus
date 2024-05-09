#include "lib/target.h"

#include <QApplication>
#include <random>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace lib;

BOOST_AUTO_TEST_SUITE(lib_target)

// random generator:
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(-1000, 1000);

BOOST_AUTO_TEST_CASE(simple_construct) {
  struct {
    double x, y;
  } cases[] = {{0, 0}, {0, 1}, {1, 0}};

  // конструктор по (double, double)
  for (auto c : cases) {
    Target t(c.x, c.y);

    BOOST_TEST(t.GetPoint().x == c.x);
    BOOST_TEST(t.GetPoint().y == c.y);
  }

  // конструктор по lib::Point
  for (auto c : cases) {
    Target t{c.x, c.y};

    BOOST_TEST(t.GetPoint().x == c.x);
    BOOST_TEST(t.GetPoint().y == c.y);
  }
}

BOOST_AUTO_TEST_CASE(random_get) {
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen);

    Target t(x, y);

    BOOST_TEST(t.GetPoint().x == x);
    BOOST_TEST(t.GetPoint().y == y);
  }
}

BOOST_AUTO_TEST_CASE(random_set) {
  Target t(0, 0);
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen);

    t.SetPoint(x, y);

    BOOST_TEST(t.GetPoint().x == x);
    BOOST_TEST(t.GetPoint().y == y);
  }
}

BOOST_AUTO_TEST_SUITE_END()
