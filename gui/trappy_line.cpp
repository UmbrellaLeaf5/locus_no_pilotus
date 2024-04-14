#include "trappy_line.h"

namespace gui {

TrappyLine::TrappyLine(std::initializer_list<gui::Target> targets) {
  UpdateData(targets);
}

void TrappyLine::SetNewTargets(std::initializer_list<gui::Target> targets) {
  UpdateData(targets);
}

void TrappyLine::Draw(QCustomPlot* plot) {
  // фигура представляет собой пунктирное красное соединение между
  // заданными контрольными точками (причем эти точки выделяются)

  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  QPen pen;
  pen.setColor(QColor(200, 50, 50, 255));
  pen.setStyle(Qt::DashLine);
  graph_->setPen(pen);

  graph_->setLineStyle(QCPGraph::lsLine);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = data_.GetTargets();

  for (int i = 0; i < targets.size(); i++) {
    graph_->addData({targets[i].GetPoint().x}, {targets[i].GetPoint().y});
  }

  // индекс последнего созданного = кол-во всех - 1
  plottable_index_ = plot->plottableCount() - 1;
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
