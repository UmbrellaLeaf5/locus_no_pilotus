#include "target.h"

namespace LIB {

json Target::Save() const { return json(); }

JSONable* Target::Load(const json& j) { return new Target(0, 0); }

}  // namespace LIB