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

  void SetTargets(gui::Target* first_target, gui::Target* second_target) {
    UpdateData(first_target, second_target);
  }

  void SetTargets(std::pair<gui::Target*, gui::Target*> targets) {
    UpdateData(targets);
  }

  std::pair<lib::Target, lib::Target> GetTargets() const {
    return data_.GetTargets();
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

  const std::pair<size_t, size_t>& GetTargetsPlottableIndexes() const {
    return targets_indexes_;
  }

  const std::pair<QCPGraph*, QCPGraph*>& GetTargetsGraphPtrs() const {
    return targets_graphs_;
  }

 private:
  void UpdateData(gui::Target* first_target, gui::Target* second_target);
  void UpdateData(std::pair<gui::Target*, gui::Target*> targets);

  lib::TrappyLine data_;
  size_t plottable_index_{ULLONG_MAX};
  QCPGraph* graph_{nullptr};

  std::pair<size_t, size_t> targets_indexes_;
  std::pair<QCPGraph*, QCPGraph*> targets_graphs_;
};

}  // namespace gui
