#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>

#include "../lib/trappy_line.h"
#include "target.h"

namespace gui {

// MEANS: фигура линии опасного перелета
class TrappyLine : public Drawable {
 public:
  TrappyLine() = default;

  TrappyLine(std::initializer_list<gui::Target> targets);

  void Draw(QCustomPlot* plot) const override;

  void SetNewTargets(std::initializer_list<gui::Target> targets);

  void AddTargets(std::initializer_list<gui::Target> targets) {
    AddData(targets);
  }

  std::vector<lib::Target> GetTargets() const { return data_.GetTargets(); }

 private:
  // DOES: обновляет объекты в приватном поле lib::TrappyLine
  // ARGS: [std::initializer_list<gui::Target>]: объекты - контр. точки
  void UpdateData(std::initializer_list<gui::Target> targets);

  // DOES: добавляет объекты в приватное поле lib::TrappyLine
  // ARGS: [std::initializer_list<gui::Target>]: объекты - контр. точки
  void AddData(std::initializer_list<gui::Target> targets);

  lib::TrappyLine data_;
};

}  // namespace gui
