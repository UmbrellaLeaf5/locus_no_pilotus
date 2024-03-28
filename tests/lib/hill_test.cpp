#include "../lib/hill.h"

#include <QApplication>
#include <cmath>
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

BOOST_AUTO_TEST_SUITE(lib_hill)

// инициализация по конструктору правильного многоугольника
BOOST_AUTO_TEST_CASE(simple_regular_construct) {
  struct {
    double x, y, r;
    size_t v_a;
  } cases[] = {{0, 0, 0, 2}, {0, 0, 1, 2}, {1, 0, 0, 3}};

  for (auto c : cases) {
    Hill h(lib::Point(c.x, c.y), c.r, c.v_a);
    //     IC(c.x, c.y, c.r, c.v_a);  // IGNORE

    BOOST_TEST(std::abs(h.GetCenter().x - c.x) < 1.0E-7);  // приближенно равны
    BOOST_TEST(std::abs(h.GetCenter().y - c.y) < 1.0E-7);  // приближенно равны
    BOOST_TEST(std::abs(h.GetRadius() - c.r) < 1.0E-7);
    BOOST_TEST(h.GetPoints().size() == c.v_a);
  }
}

BOOST_AUTO_TEST_CASE(random_regular_construct) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  std::uniform_real_distribution<> dis_pos(0, 1000);
  std::uniform_int_distribution<> dis_int(2, 1000);

  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen), r = dis_pos(gen);
    size_t v_a = dis_int(gen);

    Hill h(lib::Point(x, y), r, v_a);

    BOOST_TEST(std::abs(h.GetCenter().x - x) < 1.0E-7);  // приближенно равны
    BOOST_TEST(std::abs(h.GetCenter().y - y) < 1.0E-7);  // приближенно равны
    BOOST_TEST(std::abs(h.GetRadius() - r) < 1.0E-7);
    BOOST_TEST(h.GetPoints().size() == v_a);
  }
}

// IDK: конструктор по листу точек проверять имеет смысл?

// BOOST_AUTO_TEST_CASE(json_load, *utf::disabled()) {}
// BOOST_AUTO_TEST_CASE(json_save, *utf::disabled()) {}

BOOST_AUTO_TEST_SUITE_END()
