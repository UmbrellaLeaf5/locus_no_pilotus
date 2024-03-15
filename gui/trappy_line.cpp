#include "trappy_line.h"

namespace gui {

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

}  // namespace gui
