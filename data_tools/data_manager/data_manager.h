#pragma once

#include "gui/hill.h"
#include "gui/target.h"
#include "gui/trappy_circle.h"
#include "gui/trappy_line.h"

namespace data_tools {

// @brief класс, хранящий gui объекты и связывающий их с QCustomPlot
class DataManager {
 public:
  DataManager() = default;

  /**
   * @brief удаляет объект из менеджера по индексу
   * @param obj_type: тип объекта
   * @param index: индекс объекта в его векторе
   */
  void Remove(gui::ObjectType obj_type, size_t index);

  /// @brief очищает все вектора объектов
  void Clear();

  // ----------------------   Target methods   ----------------------

  // for gui::Target
  void Add(gui::Target t) { targets_.push_back(t); }
  void Add(std::initializer_list<gui::Target>);
  void Add(std::vector<gui::Target>);

  void Set(std::initializer_list<gui::Target>);
  void Set(std::vector<gui::Target>);

  // for lib::Target
  void Add(lib::Target data) { targets_.push_back(gui::Target(data)); }
  void Add(std::initializer_list<lib::Target>);
  void Add(std::vector<lib::Target>);

  void Set(std::initializer_list<lib::Target>);
  void Set(std::vector<lib::Target>);

  /**
   * @brief возвращает значение Targets
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Target>&: ссылки на объекты К.Т.
   */
  std::vector<gui::Target>& GetTargets() { return targets_; }

  /**
   * @brief возвращает значение Targets
   * @return const std::vector<gui::Target>&: ссылки на объекты К.Т.
   */
  const std::vector<gui::Target>& GetTargets() const { return targets_; }

  // ----------------------    Hill methods    ----------------------

  // for gui::Hill
  void Add(gui::Hill h) { hills_.push_back(h); }
  void Add(std::initializer_list<gui::Hill>);
  void Add(std::vector<gui::Hill>);

  void Set(std::initializer_list<gui::Hill>);
  void Set(std::vector<gui::Hill>);

  // for lib::Hill
  void Add(lib::Hill data) { hills_.push_back(gui::Hill(data)); }
  void Add(std::initializer_list<lib::Hill>);
  void Add(std::vector<lib::Hill>);

  void Set(std::initializer_list<lib::Hill>);
  void Set(std::vector<lib::Hill>);

  /**
   * @brief возвращает значение Hills
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Hill>&: ссылки на объекты рельефа
   */
  std::vector<gui::Hill>& GetHills() { return hills_; }

  /**
   * @brief возвращает значение Hills
   * @return const std::vector<gui::Hill>&: const ссылки на объекты рельефа
   */
  const std::vector<gui::Hill>& GetHills() const { return hills_; }

  // ---------------------- TrappyCircle methods ----------------------

  // for gui::TrappyCircle
  void Add(gui::TrappyCircle tr_c) { tr_circles_.push_back(tr_c); }
  void Add(std::initializer_list<gui::TrappyCircle>);
  void Add(std::vector<gui::TrappyCircle>);

  void Set(std::initializer_list<gui::TrappyCircle>);
  void Set(std::vector<gui::TrappyCircle>);

  // for lib::TrappyCircle
  void Add(lib::TrappyCircle data) {
    tr_circles_.push_back(gui::TrappyCircle(data));
  }
  void Add(std::initializer_list<lib::TrappyCircle>);
  void Add(std::vector<lib::TrappyCircle>);

  void Set(std::initializer_list<lib::TrappyCircle>);
  void Set(std::vector<lib::TrappyCircle>);

  /**
   * @brief возвращает значение Trappy Circles
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyCircle>&: ссылки на объекты опасной зоны
   */
  std::vector<gui::TrappyCircle>& GetTrappyCircles() { return tr_circles_; }

  /**
   * @brief возвращает значение Trappy Circles
   * @return const std::vector<gui::TrappyCircle>&: объекты опасной зоны
   */
  const std::vector<gui::TrappyCircle>& GetTrappyCircles() const {
    return tr_circles_;
  }

  // ----------------------  TrappyLine methods  ----------------------

  // for gui::TrappyLine
  void Add(gui::TrappyLine tr_l) { tr_lines_.push_back(tr_l); }
  void Add(std::initializer_list<gui::TrappyLine>);
  void Add(std::vector<gui::TrappyLine>);

  void Set(std::initializer_list<gui::TrappyLine>);
  void Set(std::vector<gui::TrappyLine>);

  // for lib::TrappyLine
  void Add(lib::TrappyLine data) { tr_lines_.push_back(gui::TrappyLine(data)); }
  void Add(std::initializer_list<lib::TrappyLine>);
  void Add(std::vector<lib::TrappyLine>);

  void Set(std::initializer_list<lib::TrappyLine>);
  void Set(std::vector<lib::TrappyLine>);

  /**
   * @brief возвращает значение Trappy Lines
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyLine>&: ссылки на объекты оп. перелета
   */
  std::vector<gui::TrappyLine>& GetTrappyLines() { return tr_lines_; }

  /**
   * @brief возвращает значение Trappy Lines
   * @return const std::vector<gui::TrappyLine>&: ссылки на объекты оп. перелета
   */
  const std::vector<gui::TrappyLine>& GetTrappyLines() const {
    return tr_lines_;
  }

 private:
  // TODO: переп. всё на указатели, чтобы исправить проблему c изменением копий
  std::vector<gui::Hill> hills_;
  std::vector<gui::Target> targets_;
  std::vector<gui::TrappyCircle> tr_circles_;
  std::vector<gui::TrappyLine> tr_lines_;
};

}  // namespace data_tools
