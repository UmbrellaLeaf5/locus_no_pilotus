#pragma once
#include "trajectory.h"

namespace gui {

class FlyingRobot {
 public:
  FlyingRobot() = default;

  FlyingRobot(gui::Trajectory trj)
      : trajectory_{trj}, curr_point_{trj.Segments()[0].Start()} {
    if (trajectory_.Segments()[0].IsArc())
      SetStartAngleAndClockwise();
    else
      SetAnglesOfLine();
  }

  void Draw(QCustomPlot* plot);
  void ReDraw(QCustomPlot* plot);

 private:
  gui::Trajectory trajectory_;
  QCPGraph* graph_{nullptr};

  size_t index_of_segment_ = 0;
  lib::Point curr_point_;
  double cos_of_line_;
  double sin_of_line_;
  double curr_angle_on_circle_;
  bool clockwise_;

  void SetAnglesOfLine();
  void SetStartAngleAndClockwise();
  void SetNewSegment();
  void SetNewPositionOnLine();
  void SetNewPositionOnCircle();
  bool IsCloseToEndPoint();
};

}  // namespace gui