#include "target.h"

namespace LIB {

json Target::save() const { return json(); }

JSONable* Target::load(const json& j) { return new Target(0, 0); }

}  // namespace LIB