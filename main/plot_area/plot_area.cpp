#include "plot_area.h"

#include "icecream.hpp"

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (size_t i = 0; i < manager_.GetTargets().size(); i++)
    manager_.Draw(gui::ObjectType::Targets, i, plot_.get());

  for (size_t i = 0; i < manager_.GetHills().size(); i++)
    manager_.Draw(gui::ObjectType::Hills, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++)
    manager_.Draw(gui::ObjectType::TrappyCircles, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++)
    manager_.Draw(gui::ObjectType::TrappyLines, i, plot_.get());

  UpdateInfo();
  plot_->replot();
}

void PlotArea::UpdateInfo() {
  targets_info_->setText(manager_.GetTexted(gui::ObjectType::Targets));

  hills_info_->setText(manager_.GetTexted(gui::ObjectType::Hills));

  tr_circles_info_->setText(manager_.GetTexted(gui::ObjectType::TrappyCircles));

  tr_lines_info_->setText(manager_.GetTexted(gui::ObjectType::TrappyLines));
}
