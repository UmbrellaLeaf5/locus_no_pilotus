#pragma once

#include <QTableWidget>

#include "../data_manager/data_manager.h"

namespace data_tools {

/// @brief класс, упрощающий отображение классов gui в QTableWidget's
class TablesConnection : public QObject {
 public:
  /**
   * @brief инициализирует новый экземпляр Table Manager
   * @param manager: ссылка на используемый DataManager
   * (благодаря передаче по ссылке, может редактировать данные классов)
   */
  TablesConnection(DataManager* manager) : manager_{manager} {}

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
    UpdateTablesConnections();
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
  void TrappyLinesItemChanged(int row, int column);

 private:
  void UpdateTablesConnections();

  std::unique_ptr<QTableWidget> targets_table_{nullptr};
  std::unique_ptr<QTableWidget> hills_table_{nullptr};
  std::unique_ptr<QTableWidget> tr_circles_table_{nullptr};
  std::unique_ptr<QTableWidget> tr_lines_table_{nullptr};

  std::unique_ptr<DataManager> manager_;
};

}  // namespace data_tools