#pragma once
#include "trajectory.h"

namespace gui {

class FlyingRobot {
 public:
  FlyingRobot() = default;

  FlyingRobot(gui::Trajectory trj)
      : trajectory_{trj}, curr_point_{trj.Segments()[0].Start()} {}

  void Draw(QCustomPlot* plot);

 private:
  gui::Trajectory trajectory_;
  QCPGraph* graph_{nullptr};

  size_t index_of_segment_ = 0;
  lib::Point curr_point_;
};

}  // namespace gui
