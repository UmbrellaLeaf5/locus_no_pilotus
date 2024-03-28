#include "../lib/point.h"

#include <QApplication>
#include <random>

// #include "icecream.hpp"  //IGNORE

// #include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace lib;

BOOST_AUTO_TEST_SUITE(lib_point)

BOOST_AUTO_TEST_CASE(simple_construct) {
  struct {
    double x, y;
  } cases[] = {{0, 0}, {0, 1}, {1, 0}};

  // конструктор по (double, double)
  for (auto c : cases) {
    Point p(c.x, c.y);
    BOOST_TEST(p.x == c.x);
    BOOST_TEST(p.y == c.y);
  }

  // конструктор по lib::Point
  for (auto c : cases) {
    Point p{c.x, c.y};
    BOOST_TEST(p.x == c.x);
    BOOST_TEST(p.y == c.y);
  }
}

BOOST_AUTO_TEST_CASE(random_construct) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen);
    Point p(x, y);
    BOOST_TEST(p.x == x);
    BOOST_TEST(p.y == y);
  }
}

BOOST_AUTO_TEST_CASE(simple_comparison) {
  struct {
    double x_1, y_1, x_2, y_2;
  } cases[] = {{0, 0, 0, 1}, {1, 1, 1, 1}, {2, 3, 3, 2},
               {2, 2, 2, 2}, {3, 4, 4, 4}, {5, 6, 6, 7}};

  for (auto c : cases) {
    Point p_1(c.x_1, c.y_1), p_2(c.x_2, c.y_2);

    BOOST_TEST((p_1 == p_2) == (c.x_1 == c.x_2 && c.y_1 == c.y_2));
    BOOST_TEST((p_1 != p_2) == (c.x_1 != c.x_2 || c.y_1 != c.y_2));
  }
}

BOOST_AUTO_TEST_CASE(random_comparison) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  for (int i = 0; i < 1000; i++) {
    double x_1 = dis(gen), y_1 = dis(gen);
    double x_2 = dis(gen), y_2 = dis(gen);

    Point p_1(x_1, y_1), p_2(x_2, y_2);

    BOOST_TEST((p_1 == p_2) == (x_1 == x_2 && y_1 == y_2));
  }
}

BOOST_AUTO_TEST_CASE(random_plus) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  for (int i = 0; i < 1000; i++) {
    double x_1 = dis(gen), y_1 = dis(gen);
    double x_2 = dis(gen), y_2 = dis(gen);

    Point p_1(x_1, y_1), p_2(x_2, y_2);

    BOOST_TEST((p_1 + p_2).x == x_1 + x_2);
    BOOST_TEST((p_1 + p_2).y == y_1 + y_2);

    p_1 += p_2;
    BOOST_TEST(p_1.x == x_1 + x_2);
    BOOST_TEST(p_1.y == y_1 + y_2);
  }
}

BOOST_AUTO_TEST_CASE(random_minus) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  for (int i = 0; i < 1000; i++) {
    double x_1 = dis(gen), y_1 = dis(gen);
    double x_2 = dis(gen), y_2 = dis(gen);

    Point p_1(x_1, y_1), p_2(x_2, y_2);

    BOOST_TEST((p_1 - p_2).x == x_1 - x_2);
    BOOST_TEST((p_1 - p_2).y == y_1 - y_2);

    p_1 -= p_2;
    BOOST_TEST(p_1.x == x_1 - x_2);
    BOOST_TEST(p_1.y == y_1 - y_2);
  }
}

BOOST_AUTO_TEST_SUITE_END()
