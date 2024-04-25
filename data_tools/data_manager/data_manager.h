#pragma once

#include "gui/hill.h"
#include "gui/target.h"
#include "gui/trappy_circle.h"
#include "gui/trappy_line.h"

namespace data_tools {

/// @brief Класс, хранящий gui объекты и связывающий их с QCustomPlot
class DataManager {
 public:
  DataManager() = default;

  /**
   * @brief Удаляет объект из менеджера по индексу
   * @param obj_type: тип объекта
   * @param index: индекс объекта в его векторе
   */
  void Remove(gui::ObjectType obj_type, size_t index);

  /// @brief Очищает все вектора объектов
  void Clear();

  // ----------------------   Target methods   ----------------------

  // for gui::Target
  void Add(gui::Target* t) {
    targets_.emplace_back(t);

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<gui::Target*>);
  void Add(std::vector<gui::Target*>);

  void Set(std::initializer_list<gui::Target*>);
  void Set(std::vector<gui::Target*>);

  // for lib::Target
  void Add(lib::Target data) {
    targets_.emplace_back(new gui::Target(data));

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<lib::Target>);
  void Add(std::vector<lib::Target>);

  void Set(std::initializer_list<lib::Target>);
  void Set(std::vector<lib::Target>);

  /**
   * @brief возвращает значение Targets
   * @return std::vector<gui::Target*>: указатели на объекты к.т.
   */
  std::vector<gui::Target*> GetTargetsPtrs();

  /**
   * @brief возвращает значение Targets
   * @return std::vector<gui::Target>: объекты к.т.
   */
  std::vector<gui::Target> GetTargets() const;

  // ----------------------    Hill methods    ----------------------

  // for gui::Hill
  void Add(gui::Hill* h) {
    hills_.emplace_back(h);

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<gui::Hill*>);
  void Add(std::vector<gui::Hill*>);

  void Set(std::initializer_list<gui::Hill*>);
  void Set(std::vector<gui::Hill*>);

  // for lib::Hill
  void Add(lib::Hill data) {
    hills_.emplace_back(new gui::Hill(data));

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<lib::Hill>);
  void Add(std::vector<lib::Hill>);

  void Set(std::initializer_list<lib::Hill>);
  void Set(std::vector<lib::Hill>);

  /**
   * @brief возвращает значение Hills
   * @return std::vector<gui::Hill*>: указатели на объекты рельефа
   */
  std::vector<gui::Hill*> GetHillsPtrs();

  /**
   * @brief возвращает значение Hills
   * @return std::vector<gui::Hill>: объекты рельефа
   */
  std::vector<gui::Hill> GetHills() const;

  // ---------------------- TrappyCircle methods ----------------------

  // for gui::TrappyCircle
  void Add(gui::TrappyCircle* tr_c) {
    tr_circles_.emplace_back(tr_c);

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<gui::TrappyCircle*>);
  void Add(std::vector<gui::TrappyCircle*>);

  void Set(std::initializer_list<gui::TrappyCircle*>);
  void Set(std::vector<gui::TrappyCircle*>);

  // for lib::TrappyCircle
  void Add(lib::TrappyCircle data) {
    tr_circles_.emplace_back(new gui::TrappyCircle(data));

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<lib::TrappyCircle>);
  void Add(std::vector<lib::TrappyCircle>);

  void Set(std::initializer_list<lib::TrappyCircle>);
  void Set(std::vector<lib::TrappyCircle>);

  /**
   * @brief возвращает значение Trappy Circles
   * @return std::vector<gui::TrappyCircle*>: указатели на объекты опасной зоны
   */
  std::vector<gui::TrappyCircle*> GetTrappyCirclesPtrs();

  /**
   * @brief возвращает значение Trappy Circles
   * @return std::vector<gui::TrappyCircle>: объекты опасной зоны
   */
  std::vector<gui::TrappyCircle> GetTrappyCircles() const;
  // ----------------------  TrappyLine methods  ----------------------

  // for gui::TrappyLine
  void Add(gui::TrappyLine* tr_l) {
    tr_lines_.emplace_back(tr_l);

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<gui::TrappyLine*>);
  void Add(std::vector<gui::TrappyLine*>);

  void Set(std::initializer_list<gui::TrappyLine*>);
  void Set(std::vector<gui::TrappyLine*>);

  // for lib::TrappyLine
  void Add(lib::TrappyLine data) {
    tr_lines_.emplace_back(new gui::TrappyLine(data));

    CheckErrorValues();
    RemoveLastDuplicate();
  }

  void Add(std::initializer_list<lib::TrappyLine>);
  void Add(std::vector<lib::TrappyLine>);

  void Set(std::initializer_list<lib::TrappyLine>);
  void Set(std::vector<lib::TrappyLine>);

  /**
   * @brief возвращает значение Trappy Lines
   * @return std::vector<gui::TrappyLine*>: указатели на объекты оп. перелета
   */
  std::vector<gui::TrappyLine*> GetTrappyLinesPtrs();

  /**
   * @brief возвращает значение Trappy Lines
   * @return std::vector<gui::TrappyLine>: объекты оп. перелета
   */
  std::vector<gui::TrappyLine> GetTrappyLines() const;

  /**
   * @brief Удаляет последний объект в векторах, если он является дупликатом
   * другого
   * @return true: если был удалён хоть один объект
   * @return false: если не был
   */
  bool RemoveLastDuplicate();

  /**
   * @brief Удаляет все повторяющиеся объекты в векторах объектов
   * @return true: если был удалён хоть один объект
   * @return false: если не был
   */
  bool RemoveAllDuplicates();

 private:
  /**
   * @brief Проверяет данные в DataManager на валидность
   * @throw std::invalid_argument: если объектов какого-либо вектора > 10000
   */
  void CheckErrorValues();

  std::vector<std::unique_ptr<gui::Hill>> hills_;
  std::vector<std::unique_ptr<gui::Target>> targets_;
  std::vector<std::unique_ptr<gui::TrappyCircle>> tr_circles_;
  std::vector<std::unique_ptr<gui::TrappyLine>> tr_lines_;
};

}  // namespace data_tools
