#pragma once
#include "trajectory.h"

namespace gui {

/**
 * @brief Класс, который позволяет анимировать движение робота
 * @details Представляет из себя png картинку,
 * которая движется по траектории
 */
class FlyingRobot : public Drawable {
 public:
  FlyingRobot() = default;

  /**
   * @brief Инициализирует новый экземпляр FlyingRobot
   * @param gui::Trajectory: траетория
   */
  FlyingRobot(gui::Trajectory* trj)
      : trajectory_{trj}, curr_point_{trj->Segments()[0].Start()} {
    // Сразу задаем нужные приватные поля при инициализации экземпляра класса, в
    // зависимости от того, lib::Segment является аркой или прямой линией
    if (trajectory_->Segments()[0].IsArc())
      UpdateCircleFields();
    else
      UpdateLineFields();
  }

  /**
   * @brief Отрисовывает png картинку
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;

  void UnDraw(QCustomPlot* plot);

  /**
   * @brief Эта функция нужна для того, чтобы обновлять позицию картинки на
   * полотне
   * @param plot: указатель на полотно
   */
  void ReDraw(QCustomPlot* plot);

  void SetTrajectory(gui::Trajectory* trj) {
    trajectory_ = trj;
    if (!trajectory_) return;

    curr_point_ = trj->Segments()[0].Start();
    index_of_segment_ = 0;

    if (trajectory_->Segments()[0].IsArc())
      UpdateCircleFields();
    else
      UpdateLineFields();
  }

  gui::Trajectory* GetTrajectory() const { return trajectory_; }

 private:
  gui::Trajectory* trajectory_;
  QCPGraph* graph_{nullptr};

  size_t index_of_segment_ = 0;
  lib::Point curr_point_;

  // Количество отрезков, на которые будет делиться lib::Segment
  int count_of_partitions_;

  // Поля для положения на линии
  double cos_of_line_;
  double sin_of_line_;

  // Поля для положения на окружности

  double curr_angle_on_circle_;
  // Величина смещения угла
  double distribution_of_angle_;
  // Если true, что двигаемся по часовой
  bool clockwise_;

  /**
   * @brief Обновляет поля cos_of_line_ и sin_of_line_
   */
  void UpdateLineFields();

  /**
   * @brief Обновляет поля curr_angle_on_circle_, clockwise_ и
   * distribution_of_angle_
   */
  void UpdateCircleFields();

  /**
   * @brief Берет следующий Segment, обновляя приватные поля
   */
  void UpdateSegment();

  /**
   * @brief Обновляет текущее положение точки на линии
   */
  void SetNewPositionOnLine();

  /**
   * @brief Обновляет текущее положение точки на окружности
   */
  void SetNewPositionOnCircle();
};

}  // namespace gui
