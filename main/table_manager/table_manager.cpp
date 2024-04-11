#include "table_manager.h"

void TableManager::UpdateTable(const std::vector<gui::Target>& targets) {
  targets_table_->setColumnCount(targets.size());
  for (size_t i = 0; i < targets.size(); i++) {
    targets_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    targets_table_->setItem(
        0, i,
        new QTableWidgetItem(QString::number(targets[i].GetPlottableIndex())));
    targets_table_->setItem(
        1, i, new QTableWidgetItem(QString::number(targets[i].GetPoint().x)));
    targets_table_->setItem(
        2, i, new QTableWidgetItem(QString::number(targets[i].GetPoint().y)));
  }
  targets_table_->update();
}

void TableManager::UpdateTable(const std::vector<gui::Hill>& hills) {
  // находим максимально возможное кол-во точек среди всех холмов
  size_t hills_max_points = hills[0].GetPoints().size();
  for (size_t i = 0; i < hills.size() - 1; i++) {
    hills_max_points =
        std::max(hills[i].GetPoints().size(), hills[i + 1].GetPoints().size());
  }
  hills_table_->setColumnCount(hills.size());
  hills_table_->setRowCount(hills_max_points * 2 + 1);

  for (size_t i = 0; i < hills.size(); i++) {
    hills_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    hills_table_->setItem(
        0, i,
        new QTableWidgetItem(QString::number(hills[i].GetPlottableIndex())));
    for (size_t j = 1; j < hills[i].GetPoints().size() * 2; j += 2) {
      hills_table_->setVerticalHeaderItem(
          j, new QTableWidgetItem("X_" + QString::number(j / 2 + 1)));
      hills_table_->setVerticalHeaderItem(
          j + 1, new QTableWidgetItem("Y_" + QString::number(j / 2 + 1)));

      hills_table_->setItem(j, i,
                            new QTableWidgetItem(QString::number(
                                hills[i].GetPoints()[(j - 1) / 2].x)));
      hills_table_->setItem(j + 1, i,
                            new QTableWidgetItem(QString::number(
                                hills[i].GetPoints()[(j - 1) / 2].y)));
    }
  }
  hills_table_->update();
}

void TableManager::UpdateTable(
    const std::vector<gui::TrappyLine>& trappy_lines) {
  tr_lines_table_->setColumnCount(trappy_lines.size());
  for (size_t i = 0; i < trappy_lines.size(); i++) {
    tr_lines_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    tr_lines_table_->setItem(0, i,
                             new QTableWidgetItem(QString::number(
                                 trappy_lines[i].GetPlottableIndex())));
    tr_lines_table_->setItem(
        1, i,
        new QTableWidgetItem(
            QString::number(trappy_lines[i].GetTargets()[0].GetPoint().x)));
    tr_lines_table_->setItem(
        2, i,
        new QTableWidgetItem(
            QString::number(trappy_lines[i].GetTargets()[0].GetPoint().y)));
    tr_lines_table_->setItem(
        3, i,
        new QTableWidgetItem(
            QString::number(trappy_lines[i].GetTargets()[1].GetPoint().x)));
    tr_lines_table_->setItem(
        4, i,
        new QTableWidgetItem(
            QString::number(trappy_lines[i].GetTargets()[1].GetPoint().y)));
  }
  tr_lines_table_->update();
}

void TableManager::UpdateTable(
    const std::vector<gui::TrappyCircle>& trappy_circles) {
  tr_circles_table_->setColumnCount(trappy_circles.size());
  for (size_t i = 0; i < trappy_circles.size(); i++) {
    tr_circles_table_->setHorizontalHeaderItem(
        i, new QTableWidgetItem("n. " + QString::number(i + 1)));
    tr_circles_table_->setItem(0, i,
                               new QTableWidgetItem(QString::number(
                                   trappy_circles[i].GetItemIndex())));
    tr_circles_table_->setItem(
        1, i,
        new QTableWidgetItem(QString::number(trappy_circles[i].GetCenter().x)));
    tr_circles_table_->setItem(
        2, i,
        new QTableWidgetItem(QString::number(trappy_circles[i].GetCenter().y)));
    tr_circles_table_->setItem(
        3, i,
        new QTableWidgetItem(QString::number(trappy_circles[i].GetRadius())));
  }
  tr_circles_table_->update();
}
