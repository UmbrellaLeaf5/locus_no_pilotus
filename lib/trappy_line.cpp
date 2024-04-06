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

void TrappyLine::Load(QJsonObject trappy_line_obj) {
  QJsonObject p1 = trappy_line_obj.value("P1").toObject();
  double x1 = p1.value("X").toDouble();
  double y1 = p1.value("Y").toDouble();
  QJsonObject p2 = trappy_line_obj.value("P2").toObject();
  double x2 = p2.value("X").toDouble();
  double y2 = p2.value("Y").toDouble();
  SetNewTargets({{x1, y1}, {x2, y2}});
}

bool TrappyLine::IsChanged(QJsonObject trappy_line_obj) {
  QJsonObject p1_obj = trappy_line_obj.value("P1").toObject();
  QJsonObject p2_obj = trappy_line_obj.value("P2").toObject();
  Point p1 = {p1_obj.value("X").toDouble(), p1_obj.value("Y").toDouble()};
  Point p2 = {p2_obj.value("X").toDouble(), p2_obj.value("Y").toDouble()};
  return p1 != targets_[0].GetPoint() || p2 != targets_[1].GetPoint();
}

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
