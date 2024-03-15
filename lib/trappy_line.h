#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "target.h"

namespace lib {

// MEANS: линия опасного перелета
class TrappyLine : public JSONable {
 public:
  inline TrappyLine() = default;

  // конструктор происходит исключительно по КТ,
  // так как только между ними может быть перелет

  inline TrappyLine(std::initializer_list<lib::Target> targets)
      : targets_{targets} {}

  inline TrappyLine(std::vector<lib::Target> targets) : targets_{targets} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  inline void SetNewTargets(std::initializer_list<lib::Target> targets) {
    targets_ = targets;
  }

  inline void SetNewTargets(std::vector<lib::Target> targets) {
    targets_ = targets;
  }

  inline void AddTargets(std::initializer_list<lib::Target> targets) {
    for (const auto& target : targets) {
      targets_.push_back(target);
    }
  }

  inline void AddTargets(std::vector<lib::Target> targets) {
    for (const auto& target : targets) {
      targets_.push_back(target);
    }
  }

  inline std::vector<lib::Target> GetTargets() const { return targets_; }

 private:
  std::vector<Target> targets_;
};

}  // namespace lib
