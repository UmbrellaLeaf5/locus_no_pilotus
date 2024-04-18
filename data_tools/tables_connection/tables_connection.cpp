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

      // в строки добавляем индекс на полотне
      item = new QTableWidgetItem(
          QString::number(trappy_lines[i].GetPlottableIndex()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      tr_lines_table_->setItem(0, i, item);

      // нахождение номеров двух привязанных к.т. в векторе менеджера
      size_t t_1_n;
      size_t t_2_n;

      for (size_t j = 0; j < manager_->GetTargetsPtrs().size(); j++) {
        auto target_ptr = manager_->GetTargetsPtrs()[j];

        if (target_ptr == trappy_lines[i].GetTargetsPtrs().first)
          t_1_n = j + 1;  // номер  = индекс + 1
        if (target_ptr == trappy_lines[i].GetTargetsPtrs().second)
          t_2_n = j + 1;  // номер  = индекс + 1
      }

      item = new QTableWidgetItem(QString::number(t_1_n));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(1, i, item);

      item = new QTableWidgetItem(QString::number(t_2_n));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                     Qt::ItemIsEnabled);
      tr_lines_table_->setItem(2, i, item);
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
    manager_->GetTargetsPtrs()[column]->SetPoint(x_item->text().toDouble(),
                                                 y_item->text().toDouble());

    area_->Redraw();
  }
}

void TablesConnection::HillsItemChanged(int row, int column) {
  auto x_item = hills_table_->item(row, column);
  auto y_item = hills_table_->item(row, column);

  size_t p_index{ULLONG_MAX};

  // здесь важно понимать, что из-за айдишника нумерация сдвинута
  // поэтому X на нечетных, а Y на четных
  if (row % 2 == 0) {
    // если попали в Y, то предыдущий X (той же точки)
    x_item = hills_table_->item(row - 1, column);
    p_index = row / 2 - 1;
  } else {
    // если попали в X, то следующий Y (той же точки)
    y_item = hills_table_->item(row + 1, column);
    p_index = (row - 1) / 2;
  }

  if (x_item != nullptr && y_item != nullptr &&
      column < manager_->GetHills().size() &&
      p_index < manager_->GetHills()[column].GetPoints().size()) {
    manager_->GetHillsPtrs()[column]->GetPoints()[p_index].x =
        x_item->text().toDouble();
    manager_->GetHillsPtrs()[column]->GetPoints()[p_index].y =
        y_item->text().toDouble();

    area_->Redraw();
  }
}

void TablesConnection::TrappyCirclesItemChanged(int row, int column) {
  auto x_item = tr_circles_table_->item(1, column);
  auto y_item = tr_circles_table_->item(2, column);
  auto r_item = tr_circles_table_->item(3, column);

  if (x_item != nullptr && y_item != nullptr && r_item != nullptr &&
      column < manager_->GetTrappyCircles().size()) {
    manager_->GetTrappyCirclesPtrs()[column]->SetCenter(
        {x_item->text().toDouble(), y_item->text().toDouble()});
    manager_->GetTrappyCirclesPtrs()[column]->SetRadius(
        r_item->text().toDouble());

    area_->Redraw();
  }
}

void TablesConnection::TrappyLinesItemChanged(int row, int column) {
  auto t_1_item = tr_lines_table_->item(1, column);
  auto t_2_item = tr_lines_table_->item(2, column);

  if (t_1_item != nullptr && t_2_item != nullptr &&
      column < manager_->GetTrappyLines().size()) {
    // мы в клетках таблицы храним номера, так что для индекса нужно вычесть 1
    auto t_1_index = t_1_item->text().toDouble() - 1;
    auto t_2_index = t_2_item->text().toDouble() - 1;

    if (t_1_index < manager_->GetTargets().size() &&
        t_2_index < manager_->GetTargets().size()) {
      manager_->GetTrappyLinesPtrs()[column]->SetTargets(
          manager_->GetTargetsPtrs()[t_1_index],
          manager_->GetTargetsPtrs()[t_2_index]);

      area_->Redraw();
    }
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
