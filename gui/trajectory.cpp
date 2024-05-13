// header file
#include "trajectory.h"

namespace gui {

void Trajectory::Draw(QCustomPlot* plot) {
  for (auto& segment : segments_) segment.Draw(plot);
}

void Trajectory::Calculate(const std::vector<lib::Target>& targets,
                           const std::vector<lib::Hill>& hills,
                           const std::vector<lib::TrappyCircle>& tr_circles,
                           const std::vector<lib::TrappyLine>& tr_lines,
                           unsigned short amount_of_robots) {
  segments_.clear();

  if (targets.empty()) return;

  for (auto seg : math::TrajectoryCalculator(
                      targets, tr_lines, tr_circles, hills,
                      amount_of_robots)  // num_of_flyers argument needed
                      .GetTrajectory()) {
    segments_.push_back(gui::Segment(seg));
  }
}

}  // namespace gui
