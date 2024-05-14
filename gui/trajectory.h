#pragma once

// our code libs:
#include "lib/_objects.h"
#include "math/trajectory.h"
#include "segment.h"

namespace gui {

/**
 * @brief Фигура траектории облёта объектов на полотне
 * @details Ради этого мы все здесь собрались :)
 */
class Trajectory : private Drawable {
 public:
  Trajectory() = default;

  /**
   * @brief Инициализирует новый экземпляр Trajectory
   * @param segments: вектор отрезков траектории
   */
  Trajectory(const std::vector<gui::Segment>& segments) : segments_{segments} {}

  /**
   * @brief Расчет вектора сегментов по заданным объектам на полотне
   * @param targets: контрольные точки
   * @param hills: многоугольные препятствия
   * @param tr_circles: круговые препятствия
   * @param tr_lines: запрещённые перелеты
   * @param amount_of_robots: кол-во летающих роботов
   */
  void Calculate(const std::vector<lib::Target>& targets,
                 const std::vector<lib::Hill>& hills,
                 const std::vector<lib::TrappyCircle>& tr_circles,
                 const std::vector<lib::TrappyLine>& tr_lines,
                 unsigned short amount_of_robots);

  /**
   * @brief Возвращает вектор сегментов
   * @return std::vector<gui::Segment*>&
   */
  std::vector<gui::Segment>& Segments() { return segments_; }

  /**
   * @brief Возвращает вектор сегментов
   * @return const std::vector<gui::Segment*>&
   */
  const std::vector<gui::Segment>& Segments() const { return segments_; }

  /**
   * @brief Отрисовывает фигуру на полотне
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;

  void Clear() { segments_.clear(); }

 private:
  std::vector<gui::Segment> segments_;
};

}  // namespace gui
