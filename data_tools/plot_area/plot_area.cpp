#include "plot_area.h"

#include <icecream.hpp>

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (size_t i = 0; i < manager_.GetTargets().size(); i++)
    manager_.Draw(gui::GuiObjType::Targets, i, plot_.get());

  for (size_t i = 0; i < manager_.GetHills().size(); i++)
    manager_.Draw(gui::GuiObjType::Hills, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++)
    manager_.Draw(gui::GuiObjType::TrappyCircles, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++)
    manager_.Draw(gui::GuiObjType::TrappyLines, i, plot_.get());

  // UpdateInfoLabels();
  UpdateTables();
  plot_->replot();
}

void PlotArea::Remove(gui::GuiObjType obj_type, size_t index) {
  switch (obj_type) {
    case gui::GuiObjType::Targets: {
      plot_->removePlottable(manager_.GetTargets()[index].GetPlottableIndex());
      break;
    }
    case gui::GuiObjType::Hills: {
      plot_->removePlottable(manager_.GetHills()[index].GetPlottableIndex());
      break;
    }
    case gui::GuiObjType::TrappyLines: {
      plot_->removePlottable(
          manager_.GetTrappyLines()[index].GetPlottableIndex());
      break;
    }
    case gui::GuiObjType::TrappyCircles: {
      plot_->removeItem(manager_.GetTrappyCircles()[index].GetItemIndex());
      break;
    }
  }

  manager_.Remove(obj_type, index);
  Redraw();
}

void PlotArea::Clear() {
  manager_.Clear();
  Redraw();
}

void PlotArea::UpdateInfoLabels() {
  targets_label_->setText(manager_.GetTexted(gui::GuiObjType::Targets));

  hills_label_->setText(manager_.GetTexted(gui::GuiObjType::Hills));

  tr_circles_label_->setText(
      manager_.GetTexted(gui::GuiObjType::TrappyCircles));

  tr_lines_label_->setText(manager_.GetTexted(gui::GuiObjType::TrappyLines));
}

void PlotArea::UpdateTables() {
  t_connection_.UpdateTable(manager_.GetTargets());
  t_connection_.UpdateTable(manager_.GetHills());
  t_connection_.UpdateTable(manager_.GetTrappyLines());
  t_connection_.UpdateTable(manager_.GetTrappyCircles());
}
