#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "target.h"

namespace lib {

// MEANS: линия опасного перелета
class TrappyLine : public JSONable {
 public:
  TrappyLine() = default;

  // конструктор происходит исключительно по КТ,
  // так как только между ними может быть перелет

  TrappyLine(std::initializer_list<lib::Target> targets) : targets_{targets} {}

  TrappyLine(std::vector<lib::Target> targets) : targets_{targets} {}

  json Save() const override;
  JSONable* Load(const json& j) override;

  void SetNewTargets(std::initializer_list<lib::Target> targets) {
    targets_ = targets;
  }

  void SetNewTargets(std::vector<lib::Target> targets) { targets_ = targets; }

  void AddTargets(std::initializer_list<lib::Target> targets) {
    for (const auto& target : targets) {
      targets_.push_back(target);
    }
  }

  void AddTargets(std::vector<lib::Target> targets) {
    for (const auto& target : targets) {
      targets_.push_back(target);
    }
  }

  std::vector<lib::Target> GetTargets() const { return targets_; }

 private:
  std::vector<Target> targets_;
};

}  // namespace lib
