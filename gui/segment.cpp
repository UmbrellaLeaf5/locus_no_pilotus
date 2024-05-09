// header file
#include "segment.h"

// our code libs:
#include "plot_item_arc.h"

namespace gui {

std::pair<double, double> Segment::ToAnglesOnCircle() {
  auto start_angles = lib::PointAsAngles::FromPoint(Start(), Center());
  auto end_angles = lib::PointAsAngles::FromPoint(End(), Center());

  auto angle_pairs = std::array{
      std::make_pair(start_angles.positive_angle, end_angles.positive_angle),
      std::make_pair(start_angles.positive_angle, end_angles.negative_angle)};

  return *std::min_element(angle_pairs.begin(), angle_pairs.end(),
                           [](const auto& pair_1, const auto& pair_2) {
                             return std::abs(pair_1.first - pair_1.second) <
                                    std::abs(pair_2.first - pair_2.second);
                           });
}

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