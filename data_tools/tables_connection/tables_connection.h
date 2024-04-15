#pragma once

#include <QTableWidget>

#include "data_tools/plot_area/plot_area.h"

namespace data_tools {

/// @brief Класс, упрощающий отображение классов gui в QTableWidget's
class TablesConnection : public QObject {
 public:
  TablesConnection() = default;

  void Setup(DataManager* manager, PlotArea* area);

  /**
   * @brief Устанавливает значения всех таблиц с информацией
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

  /// @brief Обновляет данные в таблицах всех объектов
  void UpdateTables();

  /**
   * @brief Обновляет значения таблицы с Targets
   * @param targets: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::Target>& targets);

  /**
   * @brief Обновляет значения таблицы с Hills
   * @param hills: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::Hill>& hills);

  /**
   * @brief Обновляет значения таблицы с TrappyLines
   * @param trappy_lines: вектор новых значений
   */
  void UpdateTable(const std::vector<gui::TrappyLine>& trappy_lines);

  /**
   * @brief Обновляет значения таблицы с TrappyCircles
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
  std::unique_ptr<PlotArea> area_;
};

}  // namespace data_tools