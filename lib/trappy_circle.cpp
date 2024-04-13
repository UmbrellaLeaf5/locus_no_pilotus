#include "trappy_circle.h"

#include <stdexcept>

namespace lib {

TrappyCircle::TrappyCircle(Point center, double radius)
    : center_{center}, radius_{radius} {
  if (radius < 0)
    throw std::invalid_argument("trappy circle cannot have of negative radius");
}

QJsonObject TrappyCircle::Save(int id) const {
  QVariantMap trappy_circle_map;

  trappy_circle_map.insert("Id", id);
  trappy_circle_map.insert("X", center_.x);
  trappy_circle_map.insert("Y", center_.y);
  trappy_circle_map.insert("Radius", radius_);

  return QJsonObject::fromVariantMap(trappy_circle_map);
}

void TrappyCircle::Load(QJsonObject trappy_circle_obj) {
  if (!(trappy_circle_obj.contains("X") && trappy_circle_obj.contains("Y") &&
        trappy_circle_obj.contains("Radius")))
    throw std::invalid_argument("");
  double x = trappy_circle_obj.value("X").toDouble();
  double y = trappy_circle_obj.value("Y").toDouble();
  double r = trappy_circle_obj.value("Radius").toDouble();
  SetCenter({x, y});
  SetRadius(r);
}

bool TrappyCircle::IsChanged(QJsonObject trappy_circle_obj) {
  Point c = {trappy_circle_obj.value("X").toDouble(),
             trappy_circle_obj.value("Y").toDouble()};
  double r = trappy_circle_obj.value("Radius").toDouble();
  return c != center_ || r != radius_;
}

}  // namespace lib
