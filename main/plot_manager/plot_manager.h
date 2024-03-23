#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include "../../gui/hill.h"
#include "../../gui/target.h"
#include "../../gui/trappy_circle.h"
#include "../../gui/trappy_line.h"
#include "qcustomplot.h"

class PlotManager {
 public:
  PlotManager() : hills_(0), targets_(0), tr_circles_(0), tr_lines_(0) {}
  PlotManager(QCustomPlot* plot)
      : hills_(0), targets_(0), tr_circles_(0), tr_lines_(0), plot_(plot) {}

  enum ObjectType { Hills, Targets, TrappyCircles, TrappyLines, All };

  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  void Add(gui::Hill);
  void Add(std::initializer_list<gui::Hill>);
  void Set(std::initializer_list<gui::Hill>);
  std::vector<gui::Drawable>& GetHillsRef();
  const std::vector<gui::Drawable>& GetHills() const;

  void Add(gui::Target);
  void Add(std::initializer_list<gui::Target>);
  void Set(std::initializer_list<gui::Target>);
  std::vector<gui::Drawable>& GetTargetsRef();
  const std::vector<gui::Drawable>& GetTargets() const;

  void Add(gui::TrappyCircle);
  void Add(std::initializer_list<gui::TrappyCircle>);
  void Set(std::initializer_list<gui::TrappyCircle>);
  std::vector<gui::Drawable>& GetTrappyCirclesRef();
  const std::vector<gui::Drawable>& GetTrappyCircles() const;

  void Add(gui::TrappyLine);
  void Add(std::initializer_list<gui::TrappyLine>);
  void Set(std::initializer_list<gui::TrappyLine>);
  std::vector<gui::Drawable>& GetTrappyLinesRef();
  const std::vector<gui::Drawable>& GetTrappyLines() const;

  void Draw(ObjectType obj_type = ObjectType::All) const;

 private:
  std::unique_ptr<QCustomPlot> plot_;

  std::vector<gui::Hill> hills_;
  std::vector<gui::Target> targets_;
  std::vector<gui::TrappyCircle> tr_circles_;
  std::vector<gui::TrappyLine> tr_lines_;
};