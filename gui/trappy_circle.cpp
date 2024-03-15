#include "trappy_circle.h"

#include "qcustomplot.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(200, 50, 50, 255),
                      QColor(200, 50, 50, 100), GetRadius()));

  graph->setData({GetCenter().x}, {GetCenter().y});
}
