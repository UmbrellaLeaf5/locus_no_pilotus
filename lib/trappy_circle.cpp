#include "trappy_circle.h"

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

JSONable *TrappyCircle::Load(const json &j) { return nullptr; }

}  // namespace lib
