#include "plot_area.h"

#include <icecream.hpp>

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

  // UpdateInfoLabels();
  UpdateTables();
  plot_->replot();
}

void PlotArea::Remove(gui::ObjectType obj_type, size_t index) {
  switch (obj_type) {
    case gui::ObjectType::Targets: {
      plot_->removePlottable(manager_.GetTargets()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::Hills: {
      plot_->removePlottable(manager_.GetHills()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::TrappyLines: {
      plot_->removePlottable(
          manager_.GetTrappyLines()[index].GetPlottableIndex());
      break;
    }
    case gui::ObjectType::TrappyCircles: {
      plot_->removeItem(manager_.GetTrappyCircles()[index].GetItemIndex());
      break;
    }
  }

  manager_.Remove(obj_type, index);
  Redraw();
}

void PlotArea::UpdateInfoLabels() {
  targets_label_->setText(manager_.GetTexted(gui::ObjectType::Targets));

  hills_label_->setText(manager_.GetTexted(gui::ObjectType::Hills));

  tr_circles_label_->setText(
      manager_.GetTexted(gui::ObjectType::TrappyCircles));

  tr_lines_label_->setText(manager_.GetTexted(gui::ObjectType::TrappyLines));
}

void PlotArea::UpdateTables() {
  // targets_table_
  targets_table_->setColumnCount(manager_.GetTargets().size());
  for (size_t i = 0; i < manager_.GetTargets().size(); i++) {
    targets_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    targets_table_->setItem(0, i,
                            new QTableWidgetItem(QString::number(
                                manager_.GetTargets()[i].GetPlottableIndex())));
    targets_table_->setItem(1, i,
                            new QTableWidgetItem(QString::number(
                                manager_.GetTargets()[i].GetPoint().x)));
    targets_table_->setItem(2, i,
                            new QTableWidgetItem(QString::number(
                                manager_.GetTargets()[i].GetPoint().y)));
  }
  targets_table_->update();

  // hills_table_
  // находим максимально возможное кол-во точек среди всех холмов
  size_t hills_max_points = manager_.GetHills()[0].GetPoints().size();
  for (size_t i = 0; i < manager_.GetHills().size() - 1; i++) {
    hills_max_points = std::max(manager_.GetHills()[i].GetPoints().size(),
                                manager_.GetHills()[i + 1].GetPoints().size());
  }
  hills_table_->setColumnCount(manager_.GetHills().size());
  hills_table_->setRowCount(hills_max_points * 2 + 1);

  for (size_t i = 0; i < manager_.GetHills().size(); i++) {
    hills_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    hills_table_->setItem(0, i,
                          new QTableWidgetItem(QString::number(
                              manager_.GetHills()[i].GetPlottableIndex())));
    for (size_t j = 1; j < manager_.GetHills()[i].GetPoints().size() * 2;
         j += 2) {
      hills_table_->setVerticalHeaderItem(
          j, new QTableWidgetItem("X_" + QString::number(j / 2 + 1)));
      hills_table_->setVerticalHeaderItem(
          j + 1, new QTableWidgetItem("Y_" + QString::number(j / 2 + 1)));

      hills_table_->setItem(
          j, i,
          new QTableWidgetItem(QString::number(
              manager_.GetHills()[i].GetPoints()[(j - 1) / 2].x)));
      hills_table_->setItem(
          j + 1, i,
          new QTableWidgetItem(QString::number(
              manager_.GetHills()[i].GetPoints()[(j - 1) / 2].y)));
    }
  }
  hills_table_->update();

  // tr_circles_table_
  tr_circles_table_->setColumnCount(manager_.GetTrappyCircles().size());
  for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++) {
    tr_circles_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    tr_circles_table_->setItem(
        0, i,
        new QTableWidgetItem(
            QString::number(manager_.GetTrappyCircles()[i].GetItemIndex())));
    tr_circles_table_->setItem(
        1, i,
        new QTableWidgetItem(
            QString::number(manager_.GetTrappyCircles()[i].GetCenter().x)));
    tr_circles_table_->setItem(
        2, i,
        new QTableWidgetItem(
            QString::number(manager_.GetTrappyCircles()[i].GetCenter().y)));
    tr_circles_table_->setItem(
        3, i,
        new QTableWidgetItem(
            QString::number(manager_.GetTrappyCircles()[i].GetRadius())));
  }
  tr_circles_table_->update();

  // tr_lines_table_
  tr_lines_table_->setColumnCount(manager_.GetTrappyLines().size());
  for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++) {
    tr_lines_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    tr_lines_table_->setItem(
        0, i,
        new QTableWidgetItem(
            QString::number(manager_.GetTrappyLines()[i].GetPlottableIndex())));
    tr_lines_table_->setItem(
        1, i,
        new QTableWidgetItem(QString::number(
            manager_.GetTrappyLines()[i].GetTargets()[0].GetPoint().x)));
    tr_lines_table_->setItem(
        2, i,
        new QTableWidgetItem(QString::number(
            manager_.GetTrappyLines()[i].GetTargets()[0].GetPoint().y)));
    tr_lines_table_->setItem(
        3, i,
        new QTableWidgetItem(QString::number(
            manager_.GetTrappyLines()[i].GetTargets()[1].GetPoint().x)));
    tr_lines_table_->setItem(
        4, i,
        new QTableWidgetItem(QString::number(
            manager_.GetTrappyLines()[i].GetTargets()[1].GetPoint().y)));
  }
  tr_lines_table_->update();
}
