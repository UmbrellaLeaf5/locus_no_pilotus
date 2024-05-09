// header file
#include "plot_area.h"

namespace data_tools {

void PlotArea::Setup(DataManager* manager) { manager_.reset(manager); }

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (auto& target : manager_->GetTargetsPtrs()) target->Draw(plot_.get());

  for (auto& hill : manager_->GetHillsPtrs()) hill->Draw(plot_.get());

  for (auto& tr_circle : manager_->GetTrappyCirclesPtrs())
    tr_circle->Draw(plot_.get());

  for (auto& tr_line : manager_->GetTrappyLinesPtrs())
    tr_line->Draw(plot_.get());

  plot_->replot();
}

}  // namespace data_tools