#include "target.h"

namespace LIB {

json Target::save() const {
  return json();
}

JSONable Target::load(const json& j) const {
  // return JSONable();
}

}  // namespace LIB