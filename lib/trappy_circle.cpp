#include "trappy_circle.h"

#include <stdexcept>

namespace lib {

TrappyCircle::TrappyCircle(Point center, double radius)
    : center_{center}, radius_{radius} {
  if (radius < 0)
    throw std::invalid_argument(
        "Trappy circle cannot have of negative radius!");

  CheckErrorValues();
}

QJsonObject TrappyCircle::GetJsonInfo(int id) const {
  QVariantMap trappy_circle_map;

  trappy_circle_map.insert("Id", id);
  trappy_circle_map.insert("X", center_.x);
  trappy_circle_map.insert("Y", center_.y);
  trappy_circle_map.insert("Radius", radius_);

  return QJsonObject::fromVariantMap(trappy_circle_map);
}

void TrappyCircle::SetJsonInfo(const QJsonObject& trappy_circle_obj) {
  if (!(trappy_circle_obj.contains("X") && trappy_circle_obj.contains("Y") &&
        trappy_circle_obj.contains("Radius")))
    throw std::invalid_argument(
        "Invalid file format: missing X or Y or Radius field in "
        "TrappyCircles!");
  double x = trappy_circle_obj.value("X").toDouble();
  double y = trappy_circle_obj.value("Y").toDouble();
  double r = trappy_circle_obj.value("Radius").toDouble();
  SetCenter({x, y});
  SetRadius(r);

  CheckErrorValues();
}

bool TrappyCircle::IsChanged(const QJsonObject& trappy_circle_obj) const {
  Point c = {trappy_circle_obj.value("X").toDouble(),
             trappy_circle_obj.value("Y").toDouble()};
  double r = trappy_circle_obj.value("Radius").toDouble();
  return abs(pow(pow(center_.x, 2) + pow(center_.y, 2), 0.5) -
             pow(pow(c.x, 2) + pow(c.y, 2), 0.5)) > 10.E-7 ||
         abs(r - radius_) > 10.E-7;
}

bool TrappyCircle::operator==(const TrappyCircle& tr_circle) const {
  return center_ == tr_circle.GetCenter() && radius_ == tr_circle.GetRadius();
}

void TrappyCircle::CheckErrorValues() const {
  if (center_.x > max_coord || center_.y > max_coord || radius_ > max_coord)
    throw std::invalid_argument("Exceeding the maximum permissible values!");
}

}  // namespace lib
