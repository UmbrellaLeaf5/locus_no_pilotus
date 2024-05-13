#include "flying_robot.h"

void gui::FlyingRobot::SetNewPositionOnLine() {
  if (count_of_partitions_ == 0) {
    UpdateSegment();
  } else {
    count_of_partitions_--;

    // Полотно обновляется раз в 5 миллисекунд, скорость робота такая: смещение
    // на 1 происходит за 20 вызовов функции, поэтому мы и умножаем на 1/20
    curr_point_.x += 0.05 * cos_of_line_;
    curr_point_.y += 0.05 * sin_of_line_;
  }
}

void gui::FlyingRobot::SetNewPositionOnCircle() {
  if (count_of_partitions_ == 0)
    UpdateSegment();
  else {
    count_of_partitions_--;

    curr_point_.x = trajectory_->Segments()[index_of_segment_].Radius() *
                        cos(curr_angle_on_circle_) +
                    trajectory_->Segments()[index_of_segment_].Center().x;
    curr_point_.y = trajectory_->Segments()[index_of_segment_].Radius() *
                        sin(curr_angle_on_circle_) +
                    trajectory_->Segments()[index_of_segment_].Center().y;

    if (clockwise_)
      curr_angle_on_circle_ -= distribution_of_angle_;
    else
      curr_angle_on_circle_ += distribution_of_angle_;
  }
}

void gui::FlyingRobot::UpdateSegment() {
  index_of_segment_++;

  if (index_of_segment_ == trajectory_->Segments().size())
    index_of_segment_ = 0;

  curr_point_ = trajectory_->Segments()[index_of_segment_].Start();

  if (trajectory_->Segments()[index_of_segment_].IsArc())
    UpdateCircleFields();
  else
    UpdateLineFields();
}

void gui::FlyingRobot::UpdateLineFields() {
  lib::Point p = trajectory_->Segments()[index_of_segment_].End() -
                 trajectory_->Segments()[index_of_segment_].Start();
  double R = sqrt(p.x * p.x + p.y * p.y);

  count_of_partitions_ = lib::DistanceBetweenPoints(
                             trajectory_->Segments()[index_of_segment_].Start(),
                             trajectory_->Segments()[index_of_segment_].End()) *
                         20;

  cos_of_line_ = p.x / R;
  sin_of_line_ = p.y / R;
}

void gui::FlyingRobot::UpdateCircleFields() {
  auto angles = trajectory_->Segments()[index_of_segment_].ToAnglesOnCircle();

  double len_sector = trajectory_->Segments()[index_of_segment_].Radius() *
                      (abs(angles.second - angles.first) * M_PI / 180);

  count_of_partitions_ = len_sector * 20;
  curr_angle_on_circle_ = angles.first * M_PI / 180;
  distribution_of_angle_ =
      abs(angles.second - angles.first) / count_of_partitions_ * M_PI / 180;

  if (angles.second * M_PI / 180 - curr_angle_on_circle_ < 0)
    clockwise_ = true;
  else
    clockwise_ = false;
}

void gui::FlyingRobot::Draw(QCustomPlot* plot) {
  if (!trajectory_) throw std::invalid_argument("The trajectory is not built!");

  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);
  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(
      QCPScatterStyle(QPixmap("../images/flying_robot_pixel.png")
                          .scaled(QSize(36, 16), Qt::KeepAspectRatio)));
  graph_->setData({curr_point_.x}, {curr_point_.y});
}

void gui::FlyingRobot::ReDraw(QCustomPlot* plot) {
  if (trajectory_->Segments()[index_of_segment_].IsArc())
    SetNewPositionOnCircle();
  else
    SetNewPositionOnLine();

  graph_->setData({curr_point_.x}, {curr_point_.y});

  plot->replot();
}
