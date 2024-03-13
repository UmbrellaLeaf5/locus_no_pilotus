#include "no_direct_fly_rule.h"

namespace lib {

json TrappyLine::Save() const { return json(); }

JSONable* TrappyLine::Load(const json& j) { return nullptr; }

}  // namespace lib