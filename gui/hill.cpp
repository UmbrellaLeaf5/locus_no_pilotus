#include "hill.h"

#include "qcustomplot.h"

void gui::Hill::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(50, 200, 50, 255),
                      QColor(50, 200, 50, 100), GetRadius()));

  graph->setData({GetCenter().x}, {GetCenter().y});
}
