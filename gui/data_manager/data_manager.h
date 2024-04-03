#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include "../hill.h"
#include "../target.h"
#include "../trappy_circle.h"
#include "../trappy_line.h"
#include "qcustomplot.h"

namespace gui {

// @brief типы объектов по категориям
enum class ObjectType { Hills, Targets, TrappyCircles, TrappyLines, All };

// @brief класс, хранящий gui объекты и связывающий их с QCustomPlot
class DataManager {
 public:
  DataManager() = default;

  DataManager(QCustomPlot* plot)
      : hills_(0), targets_(0), tr_circles_(0), tr_lines_(0), plot_(plot) {}

  // @brief типы объектов по категориям
  enum ObjectType { Hills, Targets, TrappyCircles, TrappyLines, All };

  // methods

  /**
   * @brief устанавливает значение plot
   * (привязывает менеджер к полотну)
   * @param plot: указатель на полотно
   */
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  /**
   * @brief отрисовывает на полотне определенные типы объектов
   * @param obj_type: тип объектов
   * @param index: индекс объекта в его векторе
   */
  void Draw(ObjectType obj_type, size_t index);

  // ----------------------   Target methods   ----------------------

  void Add(gui::Target t) { targets_.push_back(t); }
  void Add(std::initializer_list<gui::Target>);
  void Add(std::vector<gui::Target>);
  void Add(lib::Target data) { targets_.push_back(gui::Target(data)); }

  void Set(std::initializer_list<gui::Target>);
  void Set(std::vector<gui::Target>);

  /**
   * @brief возвращает значение targets
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Target>& ссылки на объекты К.Т.
   */
  std::vector<gui::Target>& GetTargets() { return targets_; }

  /**
   * @brief возвращает значение targets
   * @return const std::vector<gui::Target>& ссылки на объекты К.Т.
   */
  const std::vector<gui::Target>& GetTargets() const { return targets_; }

  // ----------------------    Hill methods    ----------------------

  void Add(gui::Hill h) { hills_.push_back(h); }
  void Add(std::initializer_list<gui::Hill>);
  void Add(std::vector<gui::Hill>);
  void Add(lib::Hill data) { hills_.push_back(gui::Hill(data)); }

  void Set(std::initializer_list<gui::Hill>);
  void Set(std::vector<gui::Hill>);

  /**
   * @brief возвращает значение Hills
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Hill>& ссылки на объекты рельефа
   */
  std::vector<gui::Hill>& GetHills() { return hills_; }

  // RETURNS: [const std::vector<gui::Hill>&]: объекты рельефа
  const std::vector<gui::Hill>& GetHills() const { return hills_; }

  // ---------------------- TrappyCircle methods ----------------------

  void Add(gui::TrappyCircle tr_c) { tr_circles_.push_back(tr_c); }
  void Add(std::initializer_list<gui::TrappyCircle>);
  void Add(std::vector<gui::TrappyCircle>);
  void Add(lib::TrappyCircle data) {
    tr_circles_.push_back(gui::TrappyCircle(data));
  };

  void Set(std::initializer_list<gui::TrappyCircle>);
  void Set(std::vector<gui::TrappyCircle>);

  /**
   * @brief возвращает значение Trappy Circles
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyCircle>& ссылки на объекты опасной зоны
   */
  std::vector<gui::TrappyCircle>& GetTrappyCircles() { return tr_circles_; }

  /**
   * @brief возвращает значение Trappy Circles
   * @return const std::vector<gui::TrappyCircle>& объекты опасной зоны
   */
  const std::vector<gui::TrappyCircle>& GetTrappyCircles() const {
    return tr_circles_;
  }

  // ----------------------  TrappyLine methods  ----------------------

  void Add(gui::TrappyLine tr_l) { tr_lines_.push_back(tr_l); }
  void Add(std::initializer_list<gui::TrappyLine>);
  void Add(std::vector<gui::TrappyLine>);
  void Add(lib::TrappyLine data) {
    tr_lines_.push_back(gui::TrappyLine(data));
  };

  void Set(std::initializer_list<gui::TrappyLine>);
  void Set(std::vector<gui::TrappyLine>);

  /**
   * @brief возвращает значение Trappy Lines
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyLine>& ссылки на объекты оп. перелета
   */
  std::vector<gui::TrappyLine>& GetTrappyLines() { return tr_lines_; }

  /**
   * @brief возвращает значение Trappy Lines
   * @return const std::vector<gui::TrappyLine>& ссылки на объекты оп. перелета
   */
  const std::vector<gui::TrappyLine>& GetTrappyLines() const {
    return tr_lines_;
  }

  // ~methods

 private:
  std::unique_ptr<QCustomPlot> plot_;

  std::vector<gui::Hill> hills_;
  std::vector<gui::Target> targets_;
  std::vector<gui::TrappyCircle> tr_circles_;
  std::vector<gui::TrappyLine> tr_lines_;
};

}  // namespace gui