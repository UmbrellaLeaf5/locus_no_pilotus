#include "target.h"

void gui::Target::Draw(QCustomPlot* plot) {
  // фигура представляет собой малую серую окружность (точку)

  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph_->setData({GetPoint().x}, {GetPoint().y});

  // индекс последнего созданного = кол-во всех - 1
  plottable_index_ = plot->plottableCount() - 1;
}
