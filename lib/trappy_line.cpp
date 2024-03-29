#include "trappy_line.h"

namespace lib {

json TrappyLine::Save() const { return json(); }

JSONable* TrappyLine::Load(const json& j) { return nullptr; }

void TrappyLine::AddTargets(std::initializer_list<lib::Target> targets) {
  for (const auto& target : targets) {
    targets_.push_back(target);
  }
}

void TrappyLine::AddTargets(std::vector<lib::Target> targets) {
  for (const auto& target : targets) {
    targets_.push_back(target);
  }
}

}  // namespace lib
