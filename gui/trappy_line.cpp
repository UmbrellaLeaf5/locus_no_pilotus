#include "trappy_line.h"

namespace gui {

void TrappyLine::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(200, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = trappy_line_.GetTargets();

  for (int i = 0; i < targets.size() - 1; i++) {
    QPen pen;
    pen.setColor(QColor(200, 50, 50, 255));
    pen.setStyle(Qt::SolidLine);
    graph->setPen(pen);

    graph->setData({targets[i].GetPoint().x, targets[i + 1].GetPoint().x},
                   {targets[i].GetPoint().y, targets[i + 1].GetPoint().y});

    graph = plot->addGraph(plot->xAxis, plot->yAxis);

    pen.setStyle(Qt::DashLine);
    graph->setPen(pen);

    graph->setData(
        QVector<double>{targets[i].GetPoint().x, targets[i + 1].GetPoint().x},
        QVector<double>{targets[i].GetPoint().y, targets[i + 1].GetPoint().y});
  }
}

}  // namespace gui
