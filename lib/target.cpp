#include "target.h"

namespace lib {

QJsonObject Target::Save(int id) const {
  QVariantMap target_map;

  target_map.insert("Id", id);
  target_map.insert("X", p_.x);
  target_map.insert("Y", p_.y);

  return QJsonObject::fromVariantMap(target_map);
}

void Target::Load(QJsonObject target_obj) {
  double x = target_obj.value("X").toDouble();
  double y = target_obj.value("Y").toDouble();
  SetPoint({x, y});
}

}  // namespace lib
