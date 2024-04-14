#pragma once

#include "lib/trappy_line.h"
#include "target.h"

namespace gui {

/// @brief фигура линии опасного перелета
class TrappyLine : public Drawable {
 public:
  TrappyLine() = default;

  TrappyLine(std::initializer_list<gui::Target> targets);

  TrappyLine(const lib::TrappyLine& data) : data_(data){};

  TrappyLine(const TrappyLine&) = default;
  TrappyLine(TrappyLine&&) = default;

  TrappyLine& operator=(const TrappyLine&) = default;
  TrappyLine& operator=(TrappyLine&&) = default;

  void SetNewTargets(std::initializer_list<gui::Target> targets);

  void AddTargets(std::initializer_list<gui::Target> targets) {
    AddData(targets);
  }

  std::vector<lib::Target> GetTargets() const { return data_.GetTargets(); }
  lib::TrappyLine GetData() const { return data_; }

  void Draw(QCustomPlot* plot) override;

  size_t GetPlottableIndex() const { return plottable_index_; }

 private:
  /**
   * @brief обновляет объекты в приватном поле lib::TrappyLine
   * @param targets: объекты - контр. точки
   */
  void UpdateData(std::initializer_list<gui::Target> targets);

  /**
   * @brief добавляет объекты в приватное поле lib::TrappyLine
   * @param targets: объекты - контр. точки
   */
  void AddData(std::initializer_list<gui::Target> targets);

  lib::TrappyLine data_;
  size_t plottable_index_{ULLONG_MAX};
};

}  // namespace gui
