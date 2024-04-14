#include "plot_area.h"

#include <icecream.hpp>

namespace data_tools {

void PlotArea::Setup(DataManager* manager, TablesConnection* t_connection) {
  manager_.reset(manager);
  t_connection_.reset(t_connection);
}

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

  t_connection_->UpdateTables();
  plot_->replot();
}

}  // namespace data_tools