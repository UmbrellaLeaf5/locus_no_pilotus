#include "trappy_line.h"

#include <stdexcept>

namespace lib {

QJsonObject TrappyLine::GetJsonInfo(int id) const {
  QVariantMap trappy_line_map;
  QVariantMap p1_map;
  QVariantMap p2_map;

  trappy_line_map.insert("Id", id);

  p1_map.insert("X", targets_.first->GetPoint().x);
  p1_map.insert("Y", targets_.first->GetPoint().y);
  p2_map.insert("X", targets_.second->GetPoint().x);
  p2_map.insert("Y", targets_.second->GetPoint().y);

  trappy_line_map.insert("P1", p1_map);
  trappy_line_map.insert("P2", p2_map);

  return QJsonObject::fromVariantMap(trappy_line_map);
}

void TrappyLine::SetJsonInfo(const QJsonObject& trappy_line_obj) {
  if (!(trappy_line_obj.contains("P1") && trappy_line_obj.contains("P2")))
    throw std::invalid_argument("");

  QJsonObject p1 = trappy_line_obj.value("P1").toObject();
  if (!(p1.contains("X") && p1.contains("Y"))) throw std::invalid_argument("");
  double x1 = p1.value("X").toDouble();
  double y1 = p1.value("Y").toDouble();

  QJsonObject p2 = trappy_line_obj.value("P2").toObject();
  if (!(p2.contains("X") && p2.contains("Y"))) throw std::invalid_argument("");
  double x2 = p2.value("X").toDouble();
  double y2 = p2.value("Y").toDouble();
  SetTargets({new Target(x1, y1), new Target(x2, y2)});
}

bool TrappyLine::IsChanged(const QJsonObject& trappy_line_obj) const {
  QJsonObject p1_obj = trappy_line_obj.value("P1").toObject();
  QJsonObject p2_obj = trappy_line_obj.value("P2").toObject();
  Point p1 = {p1_obj.value("X").toDouble(), p1_obj.value("Y").toDouble()};
  Point p2 = {p2_obj.value("X").toDouble(), p2_obj.value("Y").toDouble()};
  return p1 != targets_.first->GetPoint() || p2 != targets_.second->GetPoint();
}

}  // namespace lib
