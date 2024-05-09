#include "flying_robot.h"

constexpr double distribution = 0.03;

void gui::FlyingRobot::SetNewSegment() {
  index_of_segment_++;

  if (index_of_segment_ == trajectory_.Segments().size()) index_of_segment_ = 0;

  curr_point_ = trajectory_.Segments()[index_of_segment_].Start();

  if (trajectory_.Segments()[index_of_segment_].IsArc())
    SetStartAngleAndClockwise();
  else
    SetAnglesOfLine();
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

bool gui::FlyingRobot::IsCloseToEndPoint() {
  lib::Point new_p =
      curr_point_ - trajectory_.Segments()[index_of_segment_].End();

  return sqrt(new_p.x * new_p.x + new_p.y * new_p.y) < 0.1;
}

void gui::FlyingRobot::SetNewPositionOnLine() {
  if (IsCloseToEndPoint())
    SetNewSegment();
  else {
    curr_point_.x += distribution * cos_of_line_;
    curr_point_.y += distribution * sin_of_line_;
  }
}

void gui::FlyingRobot::SetNewPositionOnCircle() {
  if (IsCloseToEndPoint())
    SetNewSegment();
  else {
    curr_point_.x = trajectory_.Segments()[index_of_segment_].Radius() *
                        cos(curr_angle_on_circle_) +
                    trajectory_.Segments()[index_of_segment_].Center().x;
    curr_point_.y = trajectory_.Segments()[index_of_segment_].Radius() *
                        sin(curr_angle_on_circle_) +
                    trajectory_.Segments()[index_of_segment_].Center().y;

    if (clockwise_)
      curr_angle_on_circle_ -= distribution;
    else
      curr_angle_on_circle_ += distribution;
  }
}

void gui::FlyingRobot::Draw(QCustomPlot* plot) {
  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph_->setData({curr_point_.x}, {curr_point_.y});
}

void gui::FlyingRobot::ReDraw(QCustomPlot* plot) {
  if (trajectory_.Segments()[index_of_segment_].IsArc())
    SetNewPositionOnCircle();
  else
    SetNewPositionOnLine();
  graph_->setData({curr_point_.x}, {curr_point_.y});

  plot->replot();
}
