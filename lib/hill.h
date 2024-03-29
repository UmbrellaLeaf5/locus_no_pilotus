#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "point.h"

namespace lib {

// @brief рельеф с высотой
class Hill : public JSONable {
 public:
  Hill() = default;

  /**
   * @brief инициализирует новый экземпляр Hill
   * (по радиусу и центру описанной окружности, если он правильный)
   * @param center: центр описанной окружности
   * @param radius: радиус описанной окружности
   * @param vertices_amount: кол-во вершин
   * @throw std::invalid_argument: если кол-во вершин 1 или 0
   * @throw std::invalid_argument: если радиус < 0
   */
  Hill(Point center, double radius, std::size_t vertices_amount);

  /**
   * @brief инициализирует новый экземпляр Hill
   * (так как рельеф является многоугольником, его можно построить по точкам)
   * @param points: список точек
   * @throw std::invalid_argument: если кол-во вершин 1 или 0
   */
  Hill(std::initializer_list<Point> points);

  json Save() const override;
  JSONable* Load(const json& j) override;

  Point GetCenter() const;
  double GetRadius() const;

  std::vector<Point> GetPoints() const { return vertices_; }

 private:
  std::vector<Point> vertices_;
};

}  // namespace lib
