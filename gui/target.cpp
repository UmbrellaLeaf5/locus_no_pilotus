#include "target.h"

#include "qcustomplot.h"

void gui::Target::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(50, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  QVector<double> x(1), y(1);
  x[0] = GetPoint().x;
  y[0] = GetPoint().y;
  graph->setData(x, y);
}
