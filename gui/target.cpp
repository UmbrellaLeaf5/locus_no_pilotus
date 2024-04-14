#include "target.h"

void gui::Target::Draw(QCustomPlot* plot) {
  // фигура представляет собой малую серую окружность (точку)

  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  graph->setPen(QColor(50, 50, 50, 255));
  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph->setData({GetPoint().x}, {GetPoint().y});

  // индекс последнего созданного = кол-во всех - 1
  plottable_index_ = plot->plottableCount() - 1;
}
