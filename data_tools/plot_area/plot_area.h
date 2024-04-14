#pragma once

#include <memory>

#include "data_tools/data_manager/data_manager.h"
#include "data_tools/tables_connection/tables_connection.h"
#include "gui/hill.h"
#include "gui/target.h"
#include "gui/trappy_circle.h"
#include "gui/trappy_line.h"

namespace data_tools {

class TablesConnection;
class DataManager;

/// @brief класс, упрощающий управление классами gui на QCustomPlot
class PlotArea {
 public:
  PlotArea() = default;

  PlotArea(QCustomPlot* plot) : plot_{plot} {}

  void Setup(DataManager* manager, TablesConnection* t_connection);

  // methods

  /**
   * @brief устанавливает значение plot
   * @param plot: указатель на полотно
   */
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  /// @brief перерисовывает на полотне все объекты и обновляет данные
  void Redraw();

  // ~methods

 private:
  // vars

  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;

  std::unique_ptr<DataManager> manager_;
  std::unique_ptr<TablesConnection> t_connection_;

  // ~vars
};

}  // namespace data_tools
