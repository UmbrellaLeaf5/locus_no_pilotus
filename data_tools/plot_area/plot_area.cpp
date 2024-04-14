#include "plot_area.h"

#include <icecream.hpp>

namespace data_tools {

void PlotArea::Setup(DataManager* manager) { manager_.reset(manager); }

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (size_t i = 0; i < manager_->GetTargets().size(); i++)
    manager_->Draw(gui::ObjectType::Targets, i, plot_.get());

  for (size_t i = 0; i < manager_->GetHills().size(); i++)
    manager_->Draw(gui::ObjectType::Hills, i, plot_.get());

  for (size_t i = 0; i < manager_->GetTrappyCircles().size(); i++)
    manager_->Draw(gui::ObjectType::TrappyCircles, i, plot_.get());

  for (size_t i = 0; i < manager_->GetTrappyLines().size(); i++)
    manager_->Draw(gui::ObjectType::TrappyLines, i, plot_.get());

  plot_->replot();
}

}  // namespace data_tools