#pragma once

// our code libs:
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
  void ReDraw();

  gui::FlyingRobot* GetRobot() { return robot_.get(); }

  /// @brief Перерисовывает на полотне траекторию
  void ReDrawTrajectory();

 private:
  /// @brief Расчет вектора сегментов по заданным объектам на полотне
  void CalculateTrajectory();

  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;
  std::unique_ptr<DataManager> manager_;

  std::unique_ptr<gui::Trajectory> trajectory_{new gui::Trajectory()};
  std::unique_ptr<gui::FlyingRobot> robot_{new gui::FlyingRobot()};

  void CheckHills();
  void CheckTrappyCircles();
  void CheckIntersectionsBetweenTrappyCircles();
  void CheckIntersectionsBetweenHills();
};

}  // namespace data_tools
