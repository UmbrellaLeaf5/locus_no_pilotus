#pragma once

#include "point.h"
#include "trappy_circle.h"

namespace lib {

// MEANS: рельеф с высотой
class Hill : public TrappyCircle {
 public:
  Hill(Point center = {0, 0}, double radius = 0)
      : TrappyCircle(center, radius) {}
};

}  // namespace lib
