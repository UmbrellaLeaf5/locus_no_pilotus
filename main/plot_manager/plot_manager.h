#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include "../../gui/hill.h"
#include "../../gui/target.h"
#include "../../gui/trappy_circle.h"
#include "../../gui/trappy_line.h"
#include "qcustomplot.h"

// MEANS: вспомогательный класс, упрощает управление классами gui на QCustomPlot
class PlotManager {
 public:
  PlotManager() = default;

  PlotManager(QCustomPlot* plot)
      : hills_(0), targets_(0), tr_circles_(0), tr_lines_(0), plot_(plot) {}

  // MEANS: типы объектов по категориям
  enum ObjectType { Hills, Targets, TrappyCircles, TrappyLines, All };

  // methods

  // DOES: привязывает менеджер к полотну
  // ARGS: [QCustomPlot*]: указатель на полотно
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  // DOES: отрисовывает на полотне определенные категории объектов
  // ARGS: [ObjectType]: тип категории объектов
  void Draw(ObjectType obj_type = ObjectType::All) const;

  // ----------------------   Target methods   ----------------------

  void Add(gui::Target t) { targets_.push_back(t); }
  void Add(std::initializer_list<gui::Target>);
  void Set(std::initializer_list<gui::Target>);

  // RETURNS: [std::vector<gui::Target>&]: ссылки на объекты К.Т.
  // (позволяет менять объекты, т.к. ссылка не const)
  std::vector<gui::Target>& TargetsRef() { return targets_; }

  // RETURNS: [const std::vector<gui::Target>&]: объекты К.Т.
  const std::vector<gui::Target>& GetTargets() const { return targets_; }

  // ----------------------    Hill methods    ----------------------

  void Add(gui::Hill h) { hills_.push_back(h); }
  void Add(std::initializer_list<gui::Hill>);
  void Set(std::initializer_list<gui::Hill>);

  // RETURNS: [std::vector<gui::Hill>&]: ссылки на объекты рельефа
  // (позволяет менять объекты, т.к. ссылка не const)
  std::vector<gui::Hill>& HillsRef() { return hills_; }

  // RETURNS: [const std::vector<gui::Hill>&]: объекты рельефа
  const std::vector<gui::Hill>& GetHills() const { return hills_; }

  // ---------------------- TrappyCircle methods ----------------------

  void Add(gui::TrappyCircle tr_c) { tr_circles_.push_back(tr_c); }
  void Add(std::initializer_list<gui::TrappyCircle>);
  void Set(std::initializer_list<gui::TrappyCircle>);

  // RETURNS: [std::vector<gui::TrappyCircle>&]: ссылки на объекты опасной зоны
  // (позволяет менять объекты, т.к. ссылка не const)
  std::vector<gui::TrappyCircle>& TrappyCirclesRef() { return tr_circles_; }

  // RETURNS: [const std::vector<gui::TrappyCircle>&]: объекты опасной зоны
  const std::vector<gui::TrappyCircle>& GetTrappyCircles() const {
    return tr_circles_;
  }

  // ----------------------  TrappyLine methods  ----------------------

  void Add(gui::TrappyLine tr_l) { tr_lines_.push_back(tr_l); }
  void Add(std::initializer_list<gui::TrappyLine>);
  void Set(std::initializer_list<gui::TrappyLine>);

  // RETURNS: [std::vector<gui::TrappyLine>&]: ссылки на объекты оп. перелета
  // (позволяет менять объекты, т.к. ссылка не const)
  std::vector<gui::TrappyLine>& TrappyLinesRef() { return tr_lines_; }

  // RETURNS: [const std::vector<gui::TrappyLine>&]: объекты оп. перелета
  const std::vector<gui::TrappyLine>& GetTrappyLines() const {
    return tr_lines_;
  }

  // ~methods

 private:
  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;

  std::vector<gui::Hill> hills_;
  std::vector<gui::Target> targets_;
  std::vector<gui::TrappyCircle> tr_circles_;
  std::vector<gui::TrappyLine> tr_lines_;
};