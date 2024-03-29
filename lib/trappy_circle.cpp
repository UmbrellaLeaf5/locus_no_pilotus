#include "trappy_circle.h"

namespace lib {

TrappyCircle::TrappyCircle(Point center, double radius)
    : center_{center}, radius_{radius} {
  if (radius < 0)
    throw std::invalid_argument("trappy circle cannot have of negative radius");
}

json TrappyCircle::Save() const { return json(); }

JSONable *TrappyCircle::Load(const json &j) { return nullptr; }

}  // namespace lib
