// header file
#include "segment.h"

// our code libs:
#include "plot_item_arc.h"

namespace gui {

void Segment::Draw(QCustomPlot* plot) {
  if (IsArc()) {
    auto arc = new PlotItemArc(plot);

    arc->SetPen(QColor(color_));
    arc->SetCenterAndRadiusCoords(Center().x, Center().y, Radius());

    arc->SetStartAndEnd(ToAnglesOnCircle());

  } else {
    auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

    graph->setPen(QColor(color_));
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setSelectable(QCP::stNone);

    graph->addData(Start().x, Start().y);
    graph->addData(End().x, End().y);
  }
}

}  // namespace gui