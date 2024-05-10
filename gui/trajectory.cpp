// header file
#include "trajectory.h"

namespace gui {

Trajectory::Trajectory(const std::vector<lib::Target>& targets,
                       const std::vector<lib::Hill>& hills,
                       const std::vector<lib::TrappyCircle>& tr_circles,
                       const std::vector<lib::TrappyLine>& tr_lines) {
  Calculate(targets, hills, tr_circles, tr_lines);
}

void Trajectory::Draw(QCustomPlot* plot) {
  for (auto& segment : segments_) segment.Draw(plot);
}

void Trajectory::ReDraw(const std::vector<lib::Target>& targets,
                        const std::vector<lib::Hill>& hills,
                        const std::vector<lib::TrappyCircle>& tr_circles,
                        const std::vector<lib::TrappyLine>& tr_lines,
                        QCustomPlot* plot) {
  Calculate(targets, hills, tr_circles, tr_lines);
  for (auto& segment : segments_) segment.Draw(plot);
}

void Trajectory::Calculate(const std::vector<lib::Target>& targets,
                           const std::vector<lib::Hill>& hills,
                           const std::vector<lib::TrappyCircle>& tr_circles,
                           const std::vector<lib::TrappyLine>& tr_lines) {
  segments_.clear();
  for (auto seg :
       math::TrajectoryCalculator(targets, tr_lines, tr_circles, hills)
           .GetTrajectory()) {
    segments_.push_back(gui::Segment(seg));
  }
}

}  // namespace gui
