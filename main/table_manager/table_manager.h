#pragma once

#include <QTableWidget>
#include <memory>
#include <vector>

#include "../../gui/data_manager/data_manager.h"

/// @brief класс, упрощающий отображение классов gui в QTableWidget's
class TableManager : public QObject {
 public:
  TableManager(gui::DataManager& manager) : manager_{manager} {}

  TableManager(QTableWidget* targets_info, QTableWidget* hills_info,
               QTableWidget* tr_circles_info, QTableWidget* tr_lines_info)
      : targets_table_{targets_info},
        hills_table_{hills_info},
        tr_circles_table_{tr_circles_info},
        tr_lines_table_{tr_lines_info} {}

  /**
   * @brief устанавливает значения всех таблиц с информацией
   * @param hills_info: QTableWidget с информацией о hills
   * @param targets_info: QTableWidget с информацией о hills
   * @param tr_circles_info: QTableWidget с информацией о hills
   * @param tr_lines_info: QTableWidget с информацией о hills
   */
  void SetSettingsTables(QTableWidget* targets_info, QTableWidget* hills_info,
                         QTableWidget* tr_circles_info,
                         QTableWidget* tr_lines_info) {
    targets_table_.reset(targets_info);
    hills_table_.reset(hills_info);
    tr_circles_table_.reset(tr_circles_info);
    tr_lines_table_.reset(tr_lines_info);
  }

  /**
   * @brief обновляет значения таблицы с Targets
   * @param targets: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::Target>& targets);

  /**
   * @brief обновляет значения таблицы с Hills
   * @param hills: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::Hill>& hills);

  /**
   * @brief обновляет значения таблицы с TrappyLines
   * @param trappy_lines: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::TrappyLine>& trappy_lines);

  /**
   * @brief обновляет значения таблицы с TrappyCircles
   * @param trappy_circles: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::TrappyCircle>& trappy_circles);

 private slots:
  void TargetsItemChanged(int row, int column);
  void HillsItemChanged(int row, int column);
  void TrappyCirclesItemChanged(int row, int column);
  void TrappyLinesChanged(int row, int column);

 private:
  void ConnectSlotsAndSignal() {
    QObject::connect(targets_table_.get(), &QTableWidget::cellChanged, this,
                     &TableManager::TargetsItemChanged);

    QObject::connect(hills_table_.get(), &QTableWidget::cellChanged, this,
                     &TableManager::HillsItemChanged);

    QObject::connect(tr_circles_table_.get(), &QTableWidget::cellChanged, this,
                     &TableManager::TrappyCirclesItemChanged);

    QObject::connect(tr_lines_table_.get(), &QTableWidget::cellChanged, this,
                     &TableManager::TrappyLinesChanged);
  }

  std::unique_ptr<QTableWidget> targets_table_{nullptr};
  std::unique_ptr<QTableWidget> hills_table_{nullptr};
  std::unique_ptr<QTableWidget> tr_circles_table_{nullptr};
  std::unique_ptr<QTableWidget> tr_lines_table_{nullptr};

  gui::DataManager manager_;
};