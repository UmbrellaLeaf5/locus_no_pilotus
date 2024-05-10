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
  FlyingRobot(gui::Trajectory trj)
      : trajectory_{trj}, curr_point_{trj.Segments()[0].Start()} {
    // Сразу задаем нужные приватные поля при инициализации экземпляра класса, в
    // зависимости от того, lib::Segment является аркой или прямой линией
    if (trajectory_.Segments()[0].IsArc())
      SetStartAngleAndClockwise();
    else
      SetAnglesOfLine();
  }
  /**
   * @brief Отрисовывает png картинку
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;
  /**
   * @brief Эта функция нужна для того, чтобы обновлять позицию картинки на
   * полотне
   * @param plot: указатель на полотно
   */
  void ReDraw(QCustomPlot* plot);

 private:
  gui::Trajectory trajectory_;
  QCPGraph* graph_{nullptr};

  size_t index_of_segment_ = 0;
  lib::Point curr_point_;
  double cos_of_line_;
  double sin_of_line_;
  double curr_angle_on_circle_;
  bool clockwise_;

  /**
   * @brief Обновляет поля cos_of_line_ и sin_of_line_, где
   * cos_of_line_ - косинус, sin_of_line_ - синус между линией и осью Ox
   * соответственно
   */
  void SetAnglesOfLine();
  /**
   * @brief Обновляет поля curr_angle_on_circle_ и clockwise_, где
   * curr_angle_on_circle_ - текущее положение точки на окружности в радианах,
   * clockwise_ - если true, то двигаемся по часовой, если false - то против
   */
  void SetStartAngleAndClockwise();
  /**
   * @brief Берет следующий Segment, обновляя приватные поля
   */
  void SetNewSegment();
  /**
   * @brief Обновляет текущее положение точки на линии
   */
  void SetNewPositionOnLine();
  /**
   * @brief Обновляет текущее положение точки на окружности
   */
  void SetNewPositionOnCircle();
  /**
   * @brief Проверяет, что текущая точка находится близко к конечной точке
   * Segment'a
   * @return true, если точка находится близко
   */
  bool IsCloseToEndPoint();
};

}  // namespace gui
