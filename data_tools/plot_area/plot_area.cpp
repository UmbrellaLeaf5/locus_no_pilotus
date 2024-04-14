#include "plot_area.h"

#include <icecream.hpp>

namespace data_tools {

void PlotArea::Setup(DataManager* manager) { manager_.reset(manager); }

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (auto& target : manager_->GetTargets()) target.Draw(plot_.get());

  for (auto& hill : manager_->GetHills()) hill.Draw(plot_.get());

  for (auto& tr_circle : manager_->GetTrappyCircles())
    tr_circle.Draw(plot_.get());

  for (auto& tr_line : manager_->GetTrappyLines()) tr_line.Draw(plot_.get());

  plot_->replot();
}

}  // namespace data_tools