#include "plot_area.h"

#include <icecream.hpp>

namespace data_tools {

void PlotArea::Setup(DataManager* manager, TablesConnection* t_connection) {
  manager_.reset(manager);
  t_connection_.reset(t_connection);
}

void PlotArea::SetSettingsTables(QTableWidget* targets_info,
                                 QTableWidget* hills_info,
                                 QTableWidget* tr_circles_info,
                                 QTableWidget* tr_lines_info) {
  t_connection_->SetSettingsTables(targets_info, hills_info, tr_circles_info,
                                   tr_lines_info);
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

  // UpdateInfoLabels();
  UpdateTables();
  plot_->replot();
}

void PlotArea::Remove(gui::ObjectType obj_type, size_t index) {
  switch (obj_type) {
    case gui::ObjectType::Targets: {
      plot_->removePlottable(manager_->GetTargets()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::Hills: {
      plot_->removePlottable(manager_->GetHills()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::TrappyLines: {
      plot_->removePlottable(
          manager_->GetTrappyLines()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::TrappyCircles: {
      plot_->removeItem(manager_->GetTrappyCircles()[index].GetItemIndex());
      break;
    }
  }

  manager_->Remove(obj_type, index);
  Redraw();
}

void PlotArea::Clear() {
  manager_->Clear();
  Redraw();
}

void PlotArea::UpdateInfoLabels() {
  targets_label_->setText(manager_->GetTexted(gui::ObjectType::Targets));

  hills_label_->setText(manager_->GetTexted(gui::ObjectType::Hills));

  tr_circles_label_->setText(
      manager_->GetTexted(gui::ObjectType::TrappyCircles));

  tr_lines_label_->setText(manager_->GetTexted(gui::ObjectType::TrappyLines));
}

void PlotArea::UpdateTables() {
  t_connection_->UpdateTable(manager_->GetTargets());
  t_connection_->UpdateTable(manager_->GetHills());
  t_connection_->UpdateTable(manager_->GetTrappyLines());
  t_connection_->UpdateTable(manager_->GetTrappyCircles());
}

}  // namespace data_tools