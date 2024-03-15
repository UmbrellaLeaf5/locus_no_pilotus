#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>

#include "../lib/trappy_line.h"
#include "target.h"

namespace gui {

class TrappyLine : public Drawable {
 public:
  TrappyLine(std::initializer_list<gui::Target> targets);

  void Draw(QCustomPlot* plot) const override;

  void SetNewTargets(std::initializer_list<gui::Target> targets);

  inline void AddTargets(std::initializer_list<gui::Target> targets) {
    AddData(targets);
  }

  inline std::vector<lib::Target> GetTargets() const {
    return trappy_line_.GetTargets();
  }

 private:
  void UpdateData(std::initializer_list<gui::Target> targets);

  void AddData(std::initializer_list<gui::Target> targets);

  lib::TrappyLine trappy_line_;
};

}  // namespace gui
