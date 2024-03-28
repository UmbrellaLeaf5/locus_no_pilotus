#include "plot_manager.h"

void PlotManager::Add(std::initializer_list<gui::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void PlotManager::Set(std::initializer_list<gui::Hill> hills) {
  hills_ = {hills.begin(), hills.end()};
}

void PlotManager::Add(std::initializer_list<gui::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}
void PlotManager::Set(std::initializer_list<gui::Target> targets) {
  targets_ = {targets.begin(), targets.end()};
}

void PlotManager::Add(std::initializer_list<gui::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}
void PlotManager::Set(std::initializer_list<gui::TrappyCircle> tr_circles) {
  tr_circles_ = {tr_circles.begin(), tr_circles.end()};
}

void PlotManager::Add(std::initializer_list<gui::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}
void PlotManager::Set(std::initializer_list<gui::TrappyLine> tr_lines) {
  tr_lines_ = {tr_lines.begin(), tr_lines.end()};
}

void PlotManager::Draw(ObjectType obj_type) const {
  if (obj_type == ObjectType::Targets || obj_type == ObjectType::All)
    for (const auto& target : targets_) target.Draw(plot_.get());

  if (obj_type == ObjectType::Hills || obj_type == ObjectType::All)
    for (const auto& hill : hills_) hill.Draw(plot_.get());

  if (obj_type == ObjectType::TrappyCircles || obj_type == ObjectType::All)
    for (const auto& tr_circle : tr_circles_) tr_circle.Draw(plot_.get());

  if (obj_type == ObjectType::TrappyLines || obj_type == ObjectType::All)
    for (const auto& tr_line : tr_lines_) tr_line.Draw(plot_.get());

  plot_->replot();
}
