#include "target.h"

namespace lib {

QJsonObject Target::Save(int id) const {
  QVariantMap target_map;

  target_map.insert("Id", id);
  target_map.insert("X", p_.x);
  target_map.insert("Y", p_.y);

  return QJsonObject::fromVariantMap(target_map);
}

JSONable* Target::Load(const json& j) { return new Target(0, 0); }

}  // namespace lib
