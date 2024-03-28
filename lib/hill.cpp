#include "hill.h"

#include <cmath>
#include <stdexcept>
#include <string>

namespace lib {

Hill::Hill(std::initializer_list<Point> points) : vertices_{points} {
  if (points.size() == 0 || points.size() == 1)
    throw std::invalid_argument("hill cannot consist of one or zero points");
}

json Hill::Save() const { return json(); }

JSONable* Hill::Load(const json& j) { return nullptr; }

Hill::Hill(Point center, double radius, size_t vertices_amount) {
  if (vertices_amount == 0 || vertices_amount == 1)
    throw std::invalid_argument("hill cannot consist of " +
                                std::to_string(vertices_amount) + " point");

  if (radius < 0)
    throw std::invalid_argument("hill cannot have of negative radius");

  for (size_t i = 0; i < vertices_amount; i++) {
    // каждый раз двигаем точку по окружности
    // делаем это, рассчитывая угол в зависимости от кол-ва вершин

    double angle = 2.0 * M_PI * i / vertices_amount;
    double x = center.x + radius * cos(angle);
    double y = center.y + radius * sin(angle);

    vertices_.push_back({x, y});
  }
}

Point Hill::GetCenter() const {
  // центр = сумма точек/кол-во точек
  Point res(0, 0);

  for (const auto& vert : vertices_) res += vert;

  return {res.x / vertices_.size(), res.y / vertices_.size()};
}

double Hill::GetRadius() const {
  // радиус = расстояние от центра до любой вершины (т.к. центр равноудален)

  return sqrt(pow((vertices_[0].x - GetCenter().x), 2) +
              pow((vertices_[0].y - GetCenter().y), 2));
}

}  // namespace lib
