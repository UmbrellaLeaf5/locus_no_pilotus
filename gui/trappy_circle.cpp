#include "trappy_circle.h"

#include "qcustomplot.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(200, 50, 50, 255),
                      QColor(200, 50, 50, 100), GetRadius()));
  QVector<double> x(1), y(1);
  x[0] = GetCenter().x;
  y[0] = GetCenter().y;
  graph->setData(x, y);
}
