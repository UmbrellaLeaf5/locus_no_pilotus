#pragma once

#include "lib/trappy_line.h"
#include "target.h"

namespace gui {

/// @brief Фигура линии опасного перелета
class TrappyLine : public Drawable {
 public:
  TrappyLine() = default;

  TrappyLine(gui::Target* first_target, gui::Target* second_target) {
    UpdateData(first_target, second_target);
  }

  TrappyLine(std::pair<gui::Target*, gui::Target*> targets) {
    UpdateData(targets);
  }

  TrappyLine(const lib::TrappyLine& data) : data_(data) {}

  TrappyLine(const TrappyLine&) = default;
  TrappyLine(TrappyLine&&) = default;

  TrappyLine& operator=(const TrappyLine&) = default;
  TrappyLine& operator=(TrappyLine&&) = default;

  void SetFirstTarget(gui::Target* target) {
    SetTargets(target, targets_.second);
  }

  void SetSecondTarget(gui::Target* target) {
    SetTargets(targets_.first, target);
  }

  void SetTargets(gui::Target* first_target, gui::Target* second_target) {
    UpdateData(first_target, second_target);
  }

  void SetTargets(std::pair<gui::Target*, gui::Target*> targets) {
    UpdateData(targets);
  }

  const lib::TrappyLine& GetData() const { return data_; }
  lib::TrappyLine& GetData() { return data_; }

  void Draw(QCustomPlot* plot) override;

  /**
   * @brief Возвращает индекс на полотне [plottable]
   * @return size_t: индекс
   */
  size_t GetPlottableIndex() const { return plottable_index_; }

  /**
   * @brief Возвращает значение указателя на полотне
   * @return QCPGraph*: указатель
   */
  QCPGraph* GetGraphPtr() const { return graph_; }

  std::pair<gui::Target, gui::Target> GetTargets() const {
    return std::make_pair(*targets_.first, *targets_.second);
  }

  std::pair<gui::Target*, gui::Target*> GetTargetsPtrs() { return targets_; }

  const std::pair<gui::Target*, gui::Target*>& GetTargetsPtrs() const {
    return targets_;
  }

 private:
  void UpdateData(gui::Target* first_target, gui::Target* second_target);
  void UpdateData(std::pair<gui::Target*, gui::Target*> targets);

  lib::TrappyLine data_;
  size_t plottable_index_{ULLONG_MAX};
  QCPGraph* graph_{nullptr};

  // самый простой способ иметь доступ из TrappyLine к привязанным к.т.
  // здесь нет смысла использовать умные указатели, так как мы не создаём новых
  std::pair<gui::Target*, gui::Target*> targets_;
};

}  // namespace gui
