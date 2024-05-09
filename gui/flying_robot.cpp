#include "flying_robot.h"

void gui::FlyingRobot::Draw(QCustomPlot* plot) {
  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph_->setData({curr_point_.x}, {curr_point_.y});
}
