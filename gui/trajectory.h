#pragma once

// our code libs:
#include "lib/_objects.h"
#include "segment.h"

namespace gui {

/**
 * @brief Фигура траектории облёта объектов на полотне
 * @details Ради этого мы все здесь собрались :)
 */
class Trajectory : private Drawable {
 public:
  Trajectory() = default;

  Trajectory(std::vector<gui::Segment> segments) : segments_{segments} {}

  Trajectory(std::vector<lib::Target> targets, std::vector<lib::Hill> hills,
             std::vector<lib::TrappyCircle> tr_circles,
             std::vector<lib::TrappyLine> tr_lines) {
    Calculate(targets, hills, tr_circles, tr_lines);
  }

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
  void Draw(QCustomPlot* plot) override {
    for (auto& segment : segments_) segment.Draw(plot);
  }

 private:
  std::vector<gui::Segment> segments_;

  /// @brief Расчет вектора сегментов по заданным объектам на полотне
  void Calculate(std::vector<lib::Target> targets, std::vector<lib::Hill> hills,
                 std::vector<lib::TrappyCircle> tr_circles,
                 std::vector<lib::TrappyLine> tr_lines) {
    Q_UNUSED(targets);
    Q_UNUSED(hills);
    Q_UNUSED(tr_circles);
    Q_UNUSED(tr_lines);

    /**
     * Здесь должно быть использование функционала из math

     * Они должны нам вернуть std::vector<lib::Segment>,
     * которые мы переведём в std::vector<gui::Segment*>
     * и запишем в segments_
     */
  }
};

}  // namespace gui
