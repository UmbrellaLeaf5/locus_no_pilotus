#pragma once

#include <vector>

#include "base.h"
#include "target.h"

namespace lib {

class TrappyLine : public JSONable {
 public:
  inline TrappyLine() = default;

  inline TrappyLine(std::vector<lib::Target> targets) : targets_{targets} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline void SetNewTargets(std::vector<lib::Target> targets) {
    targets_ = targets;
  }

  inline void AddTarget(std::vector<lib::Target> targets) {
    for (const auto& target : targets) {
      targets_.push_back(target);
    }
  }

  inline std::vector<lib::Target> GetTargets() const { return targets_; }

 private:
  std::vector<Target> targets_;
};

}  // namespace lib