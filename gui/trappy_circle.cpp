#include "trappy_circle.h"

#include "qcustomplot.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) const {
  auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

  // фигура представляет собой красный круг с полупрозрачной заливкой

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  graph->setLineStyle(QCPGraph::lsNone);
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, color_,
                                         fill_color, GetRadius()));

  graph->setData({GetCenter().x}, {GetCenter().y});
}
