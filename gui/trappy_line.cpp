#include "trappy_line.h"

namespace gui {

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

  graph_->addData(targets.first.GetPoint().x, targets.first.GetPoint().y);
  graph_->addData(targets.second.GetPoint().x, targets.second.GetPoint().y);

  // индекс последнего созданного = кол-во всех - 1
  plottable_index_ = plot->plottableCount() - 1;
}

void TrappyLine::UpdateData(gui::Target* first_target,
                            gui::Target* second_target) {
  data_.SetTargets(&first_target->GetData(), &second_target->GetData());

  targets_.first = first_target;
  targets_.second = second_target;
}

void TrappyLine::UpdateData(std::pair<gui::Target*, gui::Target*> targets) {
  UpdateData(targets.first, targets.second);
}

}  // namespace gui
