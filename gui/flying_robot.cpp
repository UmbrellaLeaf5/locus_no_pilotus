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

void gui::FlyingRobot::SetStartAngleAndClockwise() {
  auto angles = trajectory_.Segments()[index_of_segment_].ToAnglesOnCircle();

  curr_angle_on_circle_ = angles.first * M_PI / 180;

  if (angles.second * M_PI / 180 - curr_angle_on_circle_ < 0)
    clockwise_ = true;
  else
    clockwise_ = false;
}

void gui::FlyingRobot::SetNewSegment() {
  index_of_segment_++;

  if (index_of_segment_ == trajectory_.Segments().size()) index_of_segment_ = 0;

  curr_point_ = trajectory_.Segments()[index_of_segment_].Start();

  if (trajectory_.Segments()[index_of_segment_].IsArc())
    SetStartAngleAndClockwise();
  else
    SetAnglesOfLine();
}
