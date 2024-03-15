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
  // конструктора по умолчанию быть не может, так как
  // опасная зона должна быть отрисована в конкретном месте

  TrappyLine(std::initializer_list<gui::Target> targets);

  void Draw(QCustomPlot* plot) const override;

  void SetNewTargets(std::initializer_list<gui::Target> targets);

  inline void AddTargets(std::initializer_list<gui::Target> targets) {
    AddData(targets);
  }

  inline std::vector<lib::Target> GetTargets() const {
    return data_.GetTargets();
  }

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
