#include "trappy_line.h"

namespace lib {

QJsonObject TrappyLine::Save(int id) const {
  QVariantMap trappy_line_map;
  QVariantMap p1_map;
  QVariantMap p2_map;

  trappy_line_map.insert("Id", id);

  p1_map.insert("X", targets_[0].GetPoint().x);
  p1_map.insert("Y", targets_[0].GetPoint().y);
  p2_map.insert("X", targets_[1].GetPoint().x);
  p2_map.insert("Y", targets_[1].GetPoint().y);

  trappy_line_map.insert("P1", p1_map);
  trappy_line_map.insert("P2", p2_map);

  return QJsonObject::fromVariantMap(trappy_line_map);
}

JSONable* TrappyLine::Load(const json& j) { return nullptr; }

void TrappyLine::AddTargets(std::initializer_list<lib::Target> targets) {
  for (const auto& target : targets) {
    targets_.push_back(target);
  }
}

void TrappyLine::AddTargets(std::vector<lib::Target> targets) {
  for (const auto& target : targets) {
    targets_.push_back(target);
  }
}

}  // namespace lib
