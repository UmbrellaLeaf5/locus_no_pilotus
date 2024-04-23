#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "point.h"

namespace lib {

/// @brief Рельеф с высотой
class Hill : public JSONable {
 public:
  Hill() = default;

  /**
   * @brief Инициализирует новый экземпляр Hill
   * (по радиусу и центру описанной окружности, если он правильный)
   * @param center: центр описанной окружности
   * @param radius: радиус описанной окружности
   * @param vertices_amount: кол-во вершин
   * @throw std::invalid_argument: если кол-во вершин 1 или 0
   * @throw std::invalid_argument: если радиус < 0
   */
  Hill(Point center, double radius, std::size_t vertices_amount);

  /**
   * @brief Инициализирует новый экземпляр Hill
   * (так как рельеф является многоугольником, его можно построить по точкам)
   * @param points: список точек
   * @throw std::invalid_argument: если кол-во вершин 1 или 0
   */
  Hill(std::initializer_list<Point> points);
  Hill(std::vector<Point> points) : vertices_{points} { CheckErrorValues(); }

  Hill(const Hill&) = default;
  Hill(Hill&&) = default;

  Hill& operator=(const Hill&) = default;
  Hill& operator=(Hill&&) = default;

  QJsonObject GetJsonInfo(int id) const override;
  void SetJsonInfo(const QJsonObject& hill_obj) override;
  bool IsChanged(const QJsonObject& hill_obj) const override;

  Point GetCenter() const;
  double GetRadius() const;

  const std::vector<Point>& GetPoints() const { return vertices_; }
  std::vector<Point>& GetPoints() { return vertices_; }

  void AddVertice(Point vertice) { vertices_.push_back(vertice); }

 private:
  /**
   * @brief Проверяет данные в классе на валидность
   * @throw std::invalid_argument: если одна из коорд. вершин превышает
   * максимально допустимое значение
   */
  void CheckErrorValues() const override;

  std::vector<Point> vertices_;
};

}  // namespace lib
