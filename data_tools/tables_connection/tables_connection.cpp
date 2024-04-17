#include "tables_connection.h"

#include <icecream.hpp>

namespace data_tools {

void TablesConnection::Setup(DataManager* manager, PlotArea* area) {
  manager_.reset(manager);
  area_.reset(area);
}

void TablesConnection::UpdateTable(const std::vector<gui::Target>& targets) {
  if (!targets.empty()) {
    // кол-во столбцов = кол-во к.т.
    targets_table_->setColumnCount(targets.size());

    for (size_t i = 0; i < targets.size(); i++) {
      // устанавливаем столбик с номером объекта
      auto item = new QTableWidgetItem("№ " + QString::number(i + 1));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      item->setTextAlignment(Qt::AlignCenter);
      targets_table_->setHorizontalHeaderItem(i,
                                              item);  // номер к.т. = индекс + 1

      // в строки добавляем индекс на полотне и координаты
      item =
          new QTableWidgetItem(QString::number(targets[i].GetPlottableIndex()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      targets_table_->setItem(0, i, item);

      item = new QTableWidgetItem(QString::number(targets[i].GetPoint().x));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      targets_table_->setItem(1, i, item);

      item = new QTableWidgetItem(QString::number(targets[i].GetPoint().y));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      targets_table_->setItem(2, i, item);
    }
    targets_table_->update();
  } else {
    targets_table_->setColumnCount(0);
  }
}

void TablesConnection::UpdateTable(const std::vector<gui::Hill>& hills) {
  if (!hills.empty()) {
    // находим максимально возможное кол-во точек среди всех холмов
    size_t hills_max_points = hills[0].GetPoints().size();
    for (size_t i = 0; i < hills.size() - 1; i++) {
      hills_max_points = std::max(hills[i].GetPoints().size(),
                                  hills[i + 1].GetPoints().size());
    }

    // кол-во столбцов = кол-во рельефов
    hills_table_->setColumnCount(hills.size());

    // кол-во строк = максимальное число точек * 2 (т.к. x и y) и индекс
    hills_table_->setRowCount(hills_max_points * 2 + 1);

    for (size_t i = 0; i < hills.size(); i++) {
      // устанавливаем столбик с номером объекта
      auto item = new QTableWidgetItem("№ " + QString::number(i + 1));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      item->setTextAlignment(Qt::AlignCenter);
      hills_table_->setHorizontalHeaderItem(
          i,
          item);  // номер рельефа = индекс + 1

      // в строки добавляем индекс на полотне и координаты всех точек
      item =
          new QTableWidgetItem(QString::number(hills[i].GetPlottableIndex()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      hills_table_->setItem(0, i, item);

      for (size_t j = 1; j < hills[i].GetPoints().size() * 2; j += 2) {
        // названия строк с координатами
        hills_table_->setVerticalHeaderItem(
            j, new QTableWidgetItem("X_" + QString::number(j / 2 + 1)));
        hills_table_->setVerticalHeaderItem(
            j + 1, new QTableWidgetItem("Y_" + QString::number(j / 2 + 1)));

        // сами координаты
        item = new QTableWidgetItem(
            QString::number(hills[i].GetPoints()[(j - 1) / 2].x));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                       Qt::ItemIsEnabled);
        hills_table_->setItem(j, i, item);

        item = new QTableWidgetItem(
            QString::number(hills[i].GetPoints()[(j - 1) / 2].y));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                       Qt::ItemIsEnabled);
        hills_table_->setItem(j + 1, i, item);
      }
    }
    hills_table_->update();
  } else {
    hills_table_->setColumnCount(0);
  }
}

void TablesConnection::UpdateTable(
    const std::vector<gui::TrappyLine>& trappy_lines) {
  if (!trappy_lines.empty()) {
    // кол-во столбцов = кол-во опасных линий
    tr_lines_table_->setColumnCount(trappy_lines.size());

    for (size_t i = 0; i < trappy_lines.size(); i++) {
      // устанавливаем столбик с номером объекта
      auto item = new QTableWidgetItem("№ " + QString::number(i + 1));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      item->setTextAlignment(Qt::AlignCenter);
      tr_lines_table_->setHorizontalHeaderItem(
          i,
          item);  // номер линии = индекс + 1

      // в строки добавляем индекс на полотне и координаты двух точек
      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetPlottableIndex()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      tr_lines_table_->setItem(0, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetTargets().first.GetPoint().x));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(1, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetTargets().first.GetPoint().y));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(2, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetTargets().second.GetPoint().x));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(3, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetTargets().second.GetPoint().y));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(4, i, item);
    }
    tr_lines_table_->update();
  } else {
    tr_lines_table_->setColumnCount(0);
  }
}

void TablesConnection::UpdateTable(
    const std::vector<gui::TrappyCircle>& trappy_circles) {
  if (!trappy_circles.empty()) {
    // кол-во столбцов = кол-во опасных зон
    tr_circles_table_->setColumnCount(trappy_circles.size());

    for (size_t i = 0; i < trappy_circles.size(); i++) {
      // устанавливаем столбик с номером объекта
      auto item = new QTableWidgetItem("№ " + QString::number(i + 1));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      item->setTextAlignment(Qt::AlignCenter);
      tr_circles_table_->setHorizontalHeaderItem(
          i, item);  // номер зоны = индекс + 1

      // в строки добавляем индекс на полотне и координаты точки и радиус
      item = new QTableWidgetItem(
          QString::number(trappy_circles[i].GetItemIndex()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      tr_circles_table_->setItem(0, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_circles[i].GetCenter().x));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_circles_table_->setItem(1, i, item);

      item = new QTableWidgetItem(
          QString::number(trappy_circles[i].GetCenter().y));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_circles_table_->setItem(2, i, item);

      item =
          new QTableWidgetItem(QString::number(trappy_circles[i].GetRadius()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_circles_table_->setItem(3, i, item);
    }
    tr_circles_table_->update();
  } else {
    tr_circles_table_->setColumnCount(0);
  }
}

void TablesConnection::UpdateTables() {
  UpdateTable(manager_->GetTargets());
  UpdateTable(manager_->GetHills());
  UpdateTable(manager_->GetTrappyLines());
  UpdateTable(manager_->GetTrappyCircles());
}

void TablesConnection::TargetsItemChanged(int row, int column) {
  auto x_item = targets_table_->item(1, column);
  auto y_item = targets_table_->item(2, column);

  if (x_item != nullptr && y_item != nullptr &&
      column < manager_->GetTargets().size()) {
    manager_->GetTargets()[column].SetPoint(x_item->text().toDouble(),
                                            y_item->text().toDouble());

    area_->Redraw();
  }
}

void TablesConnection::HillsItemChanged(int row, int column) {
  if (column < manager_->GetHills().size()) {
    area_->Redraw();
  }
}

void TablesConnection::TrappyCirclesItemChanged(int row, int column) {
  auto x_item = tr_circles_table_->item(1, column);
  auto y_item = tr_circles_table_->item(2, column);
  auto r_item = tr_circles_table_->item(3, column);

  if (x_item != nullptr && y_item != nullptr && r_item != nullptr &&
      column < manager_->GetTrappyCircles().size()) {
    manager_->GetTrappyCircles()[column].SetCenter(
        {x_item->text().toDouble(), y_item->text().toDouble()});
    manager_->GetTrappyCircles()[column].SetRadius(r_item->text().toDouble());

    area_->Redraw();
  }
}

void TablesConnection::TrappyLinesItemChanged(int row, int column) {
  if (column < manager_->GetTrappyLines().size()) {
    area_->Redraw();
  }
}

void TablesConnection::UpdateTablesConnections() {
  {
    QObject::connect(targets_table_.get(), &QTableWidget::cellChanged, this,
                     &TablesConnection::TargetsItemChanged);

    QObject::connect(hills_table_.get(), &QTableWidget::cellChanged, this,
                     &TablesConnection::HillsItemChanged);

    QObject::connect(tr_circles_table_.get(), &QTableWidget::cellChanged, this,
                     &TablesConnection::TrappyCirclesItemChanged);

    QObject::connect(tr_lines_table_.get(), &QTableWidget::cellChanged, this,
                     &TablesConnection::TrappyLinesItemChanged);
  }
}

}  // namespace data_tools