#include "../lib/trappy_circle.h"

#include <QApplication>
#include <random>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;
using namespace lib;

BOOST_AUTO_TEST_SUITE(lib_trappy_circle)
BOOST_AUTO_TEST_CASE(simple_construct) {
  struct {
    double x, y, r;
  } cases[] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 1}};

  // конструктор по (double, double)
  for (auto c : cases) {
    TrappyCircle t_c({c.x, c.y}, c.r);

    BOOST_TEST(t_c.GetCenter().x == c.x);
    BOOST_TEST(t_c.GetCenter().y == c.y);
    BOOST_TEST(t_c.GetRadius() == c.r);
  }

  // конструктор по lib::Point
  for (auto c : cases) {
    TrappyCircle t_c({c.x, c.y}, c.r);

    BOOST_TEST(t_c.GetCenter().x == c.x);
    BOOST_TEST(t_c.GetCenter().y == c.y);
    BOOST_TEST(t_c.GetRadius() == c.r);
  }
}

BOOST_AUTO_TEST_CASE(random_get) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  std::uniform_real_distribution<> dis_pos(0, 1000);

  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen), r = dis_pos(gen);

    TrappyCircle t_c({x, y}, r);

    BOOST_TEST(t_c.GetCenter().x == x);
    BOOST_TEST(t_c.GetCenter().y == y);
    BOOST_TEST(t_c.GetRadius() == r);
  }
}

BOOST_AUTO_TEST_CASE(random_set) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1000, 1000);
  std::uniform_real_distribution<> dis_pos(0, 1000);

  TrappyCircle t_c({0, 0}, 0);
  for (int i = 0; i < 1000; i++) {
    double x = dis(gen), y = dis(gen), r = dis_pos(gen);

    t_c.SetCenter({x, y});
    t_c.SetRadius(r);

    BOOST_TEST(t_c.GetCenter().x == x);
    BOOST_TEST(t_c.GetCenter().y == y);
    BOOST_TEST(t_c.GetRadius() == r);
  }
}

// BOOST_AUTO_TEST_CASE(json_load, *utf::disabled()) {}
// BOOST_AUTO_TEST_CASE(json_save, *utf::disabled()) {}

BOOST_AUTO_TEST_SUITE_END()
