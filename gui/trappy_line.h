#pragma once

#include <initializer_list>
#include <vector>

#include "../lib/trappy_line.h"

// #include "base.h"
#include "target.h"

namespace gui {

class TrappyLine : public Drawable {
 public:
  inline TrappyLine(std::initializer_list<gui::Target> targets)
      : trappy_line_{targets_} {
    UpdateTargets(targets);
    UpdateData();
  }

  inline TrappyLine(std::vector<gui::Target> targets) : trappy_line_{targets_} {
    UpdateTargets(targets);
    UpdateData();
  }

  void Draw(QCustomPlot* plot) const override;

  inline void SetNewTargets(std::vector<gui::Target> targets) {
    UpdateTargets(targets);
    UpdateData();
  }

  inline void AddTarget(gui::Target target) {
    targets_.push_back(target.GetData());
    UpdateData();
  }

  inline std::vector<lib::Target> GetTargets() const {
    return trappy_line_.GetTargets();
  }

 private:
  inline void UpdateData() { trappy_line_ = lib::TrappyLine(targets_); }

  inline void UpdateTargets(std::vector<gui::Target> targets) {
    targets_.clear();
    for (const auto& target : targets) {
      targets_.push_back(target.GetData());
    }
  }

  inline void UpdateTargets(std::initializer_list<gui::Target> targets) {
    targets_.clear();
    for (const auto& target : targets) {
      targets_.push_back(target.GetData());
    }
  }

  std::vector<lib::Target> targets_;
  lib::TrappyLine trappy_line_;
};

}  // namespace gui
