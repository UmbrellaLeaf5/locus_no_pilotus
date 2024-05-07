#include "trappy_line.h"

#include <stdexcept>

namespace lib {

QJsonObject TrappyLine::GetJsonInfo() const {
  QVariantMap trappy_line_map;

  trappy_line_map.insert("Id", GetId());
  trappy_line_map.insert("Id_P1", targets_.first->GetId());
  trappy_line_map.insert("Id_P2", targets_.second->GetId());

  return QJsonObject::fromVariantMap(trappy_line_map);
}

bool TrappyLine::IsChanged(const QJsonObject& trappy_line_obj) const {
  unsigned short id1 =
      static_cast<unsigned short>(trappy_line_obj.value("Id_P1").toInt());
  unsigned short id2 =
      static_cast<unsigned short>(trappy_line_obj.value("Id_P2").toInt());
  return id1 != targets_.first->GetId() || id2 != targets_.second->GetId();
}

std::pair<Target, Target> TrappyLine::GetTargets() const {
  if (targets_.first == nullptr || targets_.second == nullptr)
    throw std::runtime_error("dev: target is nullptr");

  return std::make_pair(*targets_.first, *targets_.second);
}

bool TrappyLine::operator==(const TrappyLine& tr_line) const {
  return targets_.first == tr_line.GetTargetsPtrs().first &&
         targets_.second == tr_line.GetTargetsPtrs().second;
}

}  // namespace lib
