#include "target.h"

#include "qcustomplot.h"

void gui::Target::Draw(QCustomPlot* plot) const {
  // фигура представляет собой малую серую окружность (точку)

  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(50, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph->setData({GetPoint().x}, {GetPoint().y});
}
