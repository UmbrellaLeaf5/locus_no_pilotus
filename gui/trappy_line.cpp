#include "trappy_line.h"

namespace gui {

TrappyLine::TrappyLine(std::initializer_list<gui::Target> targets) {
  if (targets.size() < 2)
    throw std::invalid_argument(
        "trappy line should be line with at least 2 targets");
  UpdateData(targets);
}

void TrappyLine::SetNewTargets(std::initializer_list<gui::Target> targets) {
  if (targets.size() < 2)
    throw std::invalid_argument(
        "trappy line should be line with at least 2 targets");
  UpdateData(targets);
}

void TrappyLine::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  // фигура представляет собой пунктирное красное соединение между
  // заданными контрольными точками (причем эти точки выделяются)

  QPen pen;
  pen.setColor(QColor(200, 50, 50, 255));
  pen.setStyle(Qt::DashLine);
  graph->setPen(pen);

  graph->setLineStyle(QCPGraph::lsLine);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = data_.GetTargets();

  for (int i = 0; i < targets.size(); i++) {
    graph->addData({targets[i].GetPoint().x}, {targets[i].GetPoint().y});
  }
}

void TrappyLine::UpdateData(std::initializer_list<gui::Target> targets) {
  std::vector<lib::Target> l_targets;
  for (const auto& target : targets) {
    l_targets.push_back(target.GetData());
  }
  data_ = lib::TrappyLine(l_targets);
}

void TrappyLine::AddData(std::initializer_list<gui::Target> targets) {
  std::vector<lib::Target> l_targets = data_.GetTargets();
  for (const auto& target : targets) {
    l_targets.push_back(target.GetData());
  }
  data_ = lib::TrappyLine(l_targets);
}

}  // namespace gui
