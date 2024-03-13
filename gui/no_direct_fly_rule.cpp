#include "no_direct_fly_rule.h"

namespace gui {

void TrappyLine::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(200, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = trappy_line_.GetTargets();
  auto x_1 = targets[0].GetPoint().x;
  QVector<double> x(targets.size()), y(targets.size());

  for (size_t i = 0; i < x.size(); i++) {
    x[i] = targets[i].GetPoint().x;
    y[i] = targets[i].GetPoint().y;
  }

  graph->setData(x, y);
}

}  // namespace gui
