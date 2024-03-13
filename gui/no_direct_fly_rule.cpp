#include "no_direct_fly_rule.h"

namespace gui {

void TrappyLine::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(200, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));

  auto targets = trappy_line_.GetTargets();

  // Добавляем график с точками
  for (int i = 0; i < targets.size() - 1; i++) {
    QVector<double> xData = {targets[i].GetPoint().x,
                             targets[i + 1].GetPoint().x};
    QVector<double> yData = {targets[i].GetPoint().y,
                             targets[i + 1].GetPoint().y};
    graph->setData(xData, yData);
  }

  // Добавляем линии для соединения попарных точек
  for (int i = 0; i < targets.size() - 1; i++) {
    graph = plot->addGraph(plot->xAxis, plot->yAxis);
    graph->setPen(QPen(Qt::red));
    graph->setData(
        QVector<double>{targets[i].GetPoint().x, targets[i + 1].GetPoint().x},
        QVector<double>{targets[i].GetPoint().y, targets[i + 1].GetPoint().y});
  }
}

}  // namespace gui
