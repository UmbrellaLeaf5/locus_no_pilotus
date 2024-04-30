#include "airport.h"

void gui::Airport::Draw(QCustomPlot* plot) {
  Target::Draw(plot);
  auto graph = plot->graph(static_cast<int>(Target::GetIndexOnPlot()));

  graph->setPen(QColor(0, 0, 0, 255));
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
}