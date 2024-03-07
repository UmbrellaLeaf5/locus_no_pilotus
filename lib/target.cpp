#include "target.h"

namespace lib {

json Target::Save() const { return json(); }

JSONable* Target::Load(const json& j) { return new Target(0, 0); }

}  // namespace lib