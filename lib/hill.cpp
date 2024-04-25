#include "hill.h"

#include <cmath>
#include <stdexcept>
#include <string>

namespace lib {

Hill::Hill(std::initializer_list<Point> points) : vertices_{points} {
  if (points.size() == 0 || points.size() == 1)
    throw std::invalid_argument("Hill cannot consist of one or zero points!");

  CheckErrorValues();
}

QJsonObject Hill::GetJsonInfo(int id) const {
  QVariantMap hill_map;
  hill_map.insert("Id", id);

  QJsonArray vertices_array;
  for (size_t i = 0; i < vertices_.size(); i++) {
    QJsonObject v_obj;
    v_obj.insert("X", vertices_[i].x);
    v_obj.insert("Y", vertices_[i].y);
    vertices_array.append(v_obj);
  }
  hill_map.insert("Vertices", vertices_array);

  return QJsonObject::fromVariantMap(hill_map);
}

void Hill::SetJsonInfo(const QJsonObject& hill_obj) {
  if (!hill_obj.contains("Vertices"))
    throw std::invalid_argument(
        "Invalid file format: missing Vertices filed in Hills!");
  QJsonArray vertices_array = hill_obj.value("Vertices").toArray();
  for (size_t i = 0; i < vertices_array.size(); i++) {
    lib::Point vertice;
    QJsonObject v_obj = vertices_array[i].toObject();
    if (!(v_obj.contains("X") && v_obj.contains("Y")))
      throw std::invalid_argument(
          "Invalid file format: missing X or Y field in Hills!");
    vertice.x = v_obj.value("X").toDouble();
    vertice.y = v_obj.value("Y").toDouble();
    vertices_.push_back(vertice);
  }

  CheckErrorValues();
}

bool Hill::IsChanged(const QJsonObject& hill_obj) const {
  QJsonArray json_vertices = hill_obj.value("Vertices").toArray();
  for (size_t i = 0; i < vertices_.size() - 1; i++) {
    QJsonObject v_obj = json_vertices[i].toObject();
    lib::Point p = {v_obj.value("X").toDouble(), v_obj.value("Y").toDouble()};
    if (abs(pow(pow(p.x, 2) + pow(p.y, 2), 0.5) -
            pow(pow(vertices_[i].x, 2) + pow(vertices_[i].y, 2), 0.5)) > 10.E-7)
      return true;
  }
  return false;
}

Hill::Hill(Point center, double radius, std::size_t vertices_amount) {
  if (vertices_amount == 0 || vertices_amount == 1)
    throw std::invalid_argument("Hill cannot consist of " +
                                std::to_string(vertices_amount) + " point!");

  if (radius < 0)
    throw std::invalid_argument("Hill cannot have of negative radius!");

  for (std::size_t i = 0; i < vertices_amount; i++) {
    // каждый раз двигаем точку по окружности
    // делаем это, рассчитывая угол в зависимости от кол-ва вершин

    double angle = 2.0 * M_PI * i / vertices_amount;
    double x = center.x + radius * cos(angle);
    double y = center.y + radius * sin(angle);

    vertices_.push_back({x, y});
  }

  CheckErrorValues();
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

bool Hill::operator==(const Hill& hill) const {
  if (vertices_.size() != hill.GetPoints().size()) return false;

  for (size_t i = 0; i < vertices_.size(); i++)
    if (vertices_[i] != hill.GetPoints()[i]) return false;

  return true;
}

void Hill::CheckErrorValues() const {
  for (const auto& vert : vertices_)
    if (vert.x > max_coord || vert.y > max_coord)
      throw std::invalid_argument("Exceeding the maximum permissible values!");
}

}  // namespace lib
