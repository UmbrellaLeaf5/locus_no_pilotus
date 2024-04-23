#include "target.h"

namespace lib {

QJsonObject Target::GetJsonInfo(int id) const {
  QVariantMap target_map;

  target_map.insert("Id", id);
  target_map.insert("X", p_.x);
  target_map.insert("Y", p_.y);

  return QJsonObject::fromVariantMap(target_map);
}

void Target::SetJsonInfo(const QJsonObject& target_obj) {
  if (!(target_obj.contains("X") && target_obj.contains("Y")))
    throw std::invalid_argument("");
  double x = target_obj.value("X").toDouble();
  double y = target_obj.value("Y").toDouble();
  SetPoint(x, y);

  CheckErrorValues();
}

bool Target::IsChanged(const QJsonObject& target_obj) const {
  Point p = {target_obj.value("X").toDouble(),
             target_obj.value("Y").toDouble()};
  return p != p_;
}

void Target::CheckErrorValues() const {
  if (p_.x > max_coord || p_.y > max_coord)
    throw std::invalid_argument("exceeding the maximum permissible values");
}

}  // namespace lib
