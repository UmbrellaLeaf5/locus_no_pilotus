#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "target.h"

namespace lib {

/// @brief линия опасного перелета
class TrappyLine : public JSONable {
 public:
  TrappyLine() = default;

  TrappyLine(Target* first_target, Target* second_target)
      : targets_{std::make_pair(first_target, second_target)} {}
  TrappyLine(std::pair<Target*, Target*> targets) : targets_{targets} {}

  TrappyLine(const TrappyLine&) = default;
  TrappyLine(TrappyLine&&) = default;

  TrappyLine& operator=(const TrappyLine&) = default;
  TrappyLine& operator=(TrappyLine&&) = default;

  QJsonObject Load(int id) const override;
  void Save(const QJsonObject& trappy_line_obj) override;
  bool IsChanged(const QJsonObject& trappy_line_obj) const override;

  void SetTargets(Target* first_target, Target* second_target) {
    targets_ = std::make_pair(first_target, second_target);
  }
  void SetTargets(std::pair<Target*, Target*> targets) { targets_ = targets; }

  std::pair<Target, Target> GetTargets() const {
    return std::make_pair(*targets_.first, *targets_.second);
  }

  std::pair<Target*, Target*>& GetTargetsPtrs() { return targets_; }

 private:
  std::pair<Target*, Target*> targets_;
};

}  // namespace lib
