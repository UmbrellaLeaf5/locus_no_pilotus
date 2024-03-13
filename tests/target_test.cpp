#include "../lib/target.h"

#include <QApplication>
#include <random>

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace lib;

BOOST_AUTO_TEST_SUITE(target)

BOOST_AUTO_TEST_CASE(zero) {
  {
    Target t(0, 0);
    BOOST_TEST(t.GetPoint().x == 0);
    BOOST_TEST(t.GetPoint().y == 0);
  }
  {
    Target t(1, 0);
    BOOST_TEST(t.GetPoint().x == 1);
    BOOST_TEST(t.GetPoint().y == 0);
  }
  {
    Target t(0, 1);
    BOOST_TEST(t.GetPoint().x == 0);
    BOOST_TEST(t.GetPoint().y == 1);
  }
}

BOOST_AUTO_TEST_CASE(random_get) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen);
    Target t(x, y);
    BOOST_TEST(t.GetPoint().x == x);
    BOOST_TEST(t.GetPoint().y == y);
  }
}

BOOST_AUTO_TEST_CASE(random_set) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  Target t(0, 0);
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen);
    t.SetPoint(x, y);
    BOOST_TEST(t.GetPoint().x == x);
    BOOST_TEST(t.GetPoint().y == y);
  }
}

// BOOST_AUTO_TEST_CASE(json_load, *utf::disabled()) {}
// BOOST_AUTO_TEST_CASE(json_save, *utf::disabled()) {}

BOOST_AUTO_TEST_SUITE_END()