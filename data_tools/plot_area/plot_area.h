#pragma once

#include <memory>

#include "data_tools/data_manager/data_manager.h"

namespace data_tools {

/// @brief Класс, упрощающий управление классами gui на QCustomPlot
class PlotArea {
 public:
  PlotArea() = default;

  PlotArea(QCustomPlot* plot) : plot_{plot} {}

  void Setup(DataManager* manager);

  /**
   * @brief Устанавливает значение plot
   * @param plot: указатель на полотно
   */
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  /// @brief Перерисовывает на полотне все объекты и обновляет данные
  void Redraw();

 private:
  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;

  std::unique_ptr<DataManager> manager_;
};

}  // namespace data_tools
