#include "hill.h"

#include "qcustomplot.h"

void gui::Hill::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(50, 200, 50, 255),
                      QColor(50, 200, 50, 100), GetRadius()));
  QVector<double> x(1), y(1);
  x[0] = GetCenter().x;
  y[0] = GetCenter().y;
  graph->setData(x, y);
}
