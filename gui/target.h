#pragma once

#include "../lib/target.h"
#include "base.h"

namespace gui {
class Target : public Drawable {
 public:
  void Draw() const override;

  inline void SetX(double x) { data.SetX(x); }
  inline void SetY(double y) { data.SetY(y); }

  inline double GetX() const { return data.GetX(); }
  inline double GetY() const { return data.GetY(); }

 private:
  lib::Target data;
};
}  // namespace gui