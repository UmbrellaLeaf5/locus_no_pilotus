#pragma once

#pragma once

#include "../lib/target.h"

namespace gui {
class Drawable {
 public:
  virtual void Draw() const = 0;
};
}  // namespace gui