#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "point.h"

namespace lib {

// MEANS: рельеф с высотой
class Hill : public JSONable {
 public:
  Hill() = default;

  // так как рельеф является многоугольником, его можно построить по точкам:

  Hill(Point center, double radius, std::size_t vertices_amount);

  // или по радиусу и центру описанной окружности, если он правильный:

  Hill(std::initializer_list<Point> points) : vertices_{points} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  Point GetCenter() const;
  double GetRadius() const;

  std::vector<Point> GetPoints() const { return vertices_; }

 private:
  std::vector<Point> vertices_;
};

}  // namespace lib
