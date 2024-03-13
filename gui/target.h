#pragma once

#include "../lib/base.h"
#include "../lib/target.h"
#include "base.h"
#include "qcustomplot.h"

namespace gui {

class Target : public Drawable {
 public:
  inline Target(double x, double y) : data_(new lib::Target(x, y)) {}
  inline Target(lib::Point p) : data_(new lib::Target(p)) {}
  inline Target() : data_(new lib::Target()) {}

  inline ~Target() { delete data_; }

  void Draw(QCustomPlot* plot) const override;

  inline void SetPoint(lib::Point p) { data_->SetPoint(p); }
  inline void SetPoint(double x, double y) { data_->SetPoint(x, y); }

  inline lib::Point GetPoint() const { return data_->GetPoint(); }

 private:
  lib::Target* data_;
};

}  // namespace gui
