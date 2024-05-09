#include "flying_robot.h"

void gui::FlyingRobot::Draw(QCustomPlot* plot) {
  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph_->setData({curr_point_.x}, {curr_point_.y});
}

void gui::FlyingRobot::SetAnglesOfLine() {
  lib::Point p = trajectory_.Segments()[index_of_segment_].End() -
                 trajectory_.Segments()[index_of_segment_].Start();
  double R = sqrt(p.x * p.x + p.y * p.y);

  cos_of_line_ = p.x / R;
  sin_of_line_ = p.y / R;
}
