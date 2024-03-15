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

  QPen pen;
  pen.setColor(QColor(200, 50, 50, 255));
  pen.setStyle(Qt::DashLine);
  graph->setPen(pen);

  graph->setLineStyle(QCPGraph::lsLine);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = trappy_line_.GetTargets();

  for (int i = 0; i < targets.size(); i++) {
    graph->addData({targets[i].GetPoint().x}, {targets[i].GetPoint().y});
  }
}

void TrappyLine::UpdateData(std::initializer_list<gui::Target> targets) {
  std::vector<lib::Target> l_targets;
  for (const auto& target : targets) {
    l_targets.push_back(target.GetData());
  }
  trappy_line_ = lib::TrappyLine(l_targets);
}

void TrappyLine::AddData(std::initializer_list<gui::Target> targets) {
  std::vector<lib::Target> l_targets = trappy_line_.GetTargets();
  for (const auto& target : targets) {
    l_targets.push_back(target.GetData());
  }
  trappy_line_ = lib::TrappyLine(l_targets);
}

}  // namespace gui
