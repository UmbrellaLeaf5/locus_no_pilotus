#include "target.h"

#include "qcustomplot.h"

void gui::Target::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  // фигура представляет собой серую окружность

  graph->setPen(QColor(50, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph->setData({GetPoint().x}, {GetPoint().y});
}
