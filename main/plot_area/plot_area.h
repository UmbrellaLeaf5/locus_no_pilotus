#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include "../../gui/data_manager/data_manager.h"
#include "qcustomplot.h"

// @brief класс, упрощающий управление классами gui на QCustomPlot
class PlotArea {
 public:
  PlotArea() = default;

  PlotArea(QCustomPlot* plot) : manager_(), plot_(plot) {}

  // methods

  /**
   * @brief устанавливает значение plot
   * (привязывает менеджер к полотну)
   * @param plot: указатель на полотно
   */
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  /**
   * @brief устанавливает значение всех лейблов с информацией
   * @param hills_info: лейбл с информацией о hills
   * @param targets_info: лейбл с информацией о targets
   * @param tr_circles_info: лейбл с информацией о trappy circles
   * @param tr_lines_info: лейбл с информацией о trappy lines
   */
  void SetSettingsLabels(QLabel* hills_info, QLabel* targets_info,
                         QLabel* tr_circles_info, QLabel* tr_lines_info) {
    hills_info_.reset(hills_info);
    targets_info_.reset(targets_info);
    tr_circles_info_.reset(tr_circles_info);
    tr_lines_info_.reset(tr_lines_info);
  }

  /**
   * @brief отрисовывает на полотне определенные типы объектов
   * @param obj_type: тип объектов
   */
  void Draw(gui::ObjectType obj_type = gui::ObjectType::All);

  // ----------------------   Target methods   ----------------------

  void Add(gui::Target t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::Target> init_list) {
    manager_.Add(init_list);
  }
  void Add(lib::Target data) { manager_.Add(data); };
  void Set(std::initializer_list<gui::Target> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::Target> vec) { manager_.Set(vec); }

  /**
   * @brief возвращает значение targets
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Target>&: ссылки на объекты К.Т.
   */
  std::vector<gui::Target>& GetTargets() { return manager_.GetTargets(); }

  /**
   * @brief возвращает значение targets
   * @return const std::vector<gui::Target>&: ссылки на объекты К.Т.
   */
  const std::vector<gui::Target>& GetTargets() const {
    return manager_.GetTargets();
  }

  // ----------------------    Hill methods    ----------------------

  void Add(gui::Hill t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::Hill> init_list) {
    manager_.Add(init_list);
  }
  void Add(lib::Hill data) { manager_.Add(data); };
  void Set(std::initializer_list<gui::Hill> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::Hill> vec) { manager_.Set(vec); }

  /**
   * @brief возвращает значение Hills
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::Hill>&: ссылки на объекты рельефа
   */
  std::vector<gui::Hill>& GetHills() { return manager_.GetHills(); }

  /**
   * @brief возвращает значение Hills
   * @return const std::vector<gui::Hill>&: ссылки на объекты рельефа
   */
  const std::vector<gui::Hill>& GetHills() const { return manager_.GetHills(); }

  // ---------------------- TrappyCircle methods ----------------------

  void Add(gui::TrappyCircle t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::TrappyCircle> init_list) {
    manager_.Add(init_list);
  }
  void Add(lib::TrappyCircle data) { manager_.Add(data); };
  void Set(std::initializer_list<gui::TrappyCircle> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::TrappyCircle> vec) { manager_.Set(vec); }

  /**
   * @brief возвращает значение Trappy Circles
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyCircle>&: ссылки на объекты опасной зоны
   */
  std::vector<gui::TrappyCircle>& GetTrappyCircles() {
    return manager_.GetTrappyCircles();
  }

  /**
   * @brief возвращает значение Trappy Circles
   * @return const std::vector<gui::TrappyCircle>&: объекты опасной зоны
   */
  const std::vector<gui::TrappyCircle>& GetTrappyCircles() const {
    return manager_.GetTrappyCircles();
  }

  // ----------------------  TrappyLine methods  ----------------------

  void Add(gui::TrappyLine t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::TrappyLine> init_list) {
    manager_.Add(init_list);
  }
  void Add(lib::TrappyLine data) { manager_.Add(data); };
  void Set(std::initializer_list<gui::TrappyLine> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::TrappyLine> vec) { manager_.Set(vec); }

  /**
   * @brief возвращает значение Trappy Lines
   * (позволяет менять объекты, т.к. ссылка не const)
   * @return std::vector<gui::TrappyLine>&: ссылки на объекты оп. перелета
   */
  std::vector<gui::TrappyLine>& GetTrappyLines() {
    return manager_.GetTrappyLines();
  }

  /**
   * @brief возвращает значение Trappy Lines
   * @return const std::vector<gui::TrappyLine>&: ссылки на объекты оп. перелета
   */
  const std::vector<gui::TrappyLine>& GetTrappyLines() const {
    return manager_.GetTrappyLines();
  }

  // ~methods

 private:
  /**
   * @brief обновляет данный в лейблах определенных типов объектов
   * @param obj_type: тип объектов
   */
  void UpdateInfo(gui::ObjectType obj_type = gui::ObjectType::All);

  // vars

  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;

  std::unique_ptr<QLabel> hills_info_{nullptr};
  std::unique_ptr<QLabel> targets_info_{nullptr};
  std::unique_ptr<QLabel> tr_circles_info_{nullptr};
  std::unique_ptr<QLabel> tr_lines_info_{nullptr};

  gui::DataManager manager_;

  // ~vars
};
