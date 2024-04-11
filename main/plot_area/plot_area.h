#pragma once

#include <qcustomplot.h>

#include <icecream.hpp>
#include <initializer_list>
#include <memory>
#include <vector>

#include "../../gui/data_manager/data_manager.h"
#include "../table_manager/table_manager.h"

// @brief класс, упрощающий управление классами gui на QCustomPlot
class PlotArea {
 public:
  PlotArea() = default;

  PlotArea(QCustomPlot* plot) : manager_(), plot_(plot) {}

  // methods

  /**
   * @brief устанавливает значение plot
   * @param plot: указатель на полотно
   */
  void SetPlot(QCustomPlot* plot) { plot_.reset(plot); }

  /**
   * @brief устанавливает значение всех лейблов с информацией
   * @param targets_info: лейбл с информацией о targets
   * @param hills_info: лейбл с информацией о hills
   * @param tr_circles_info: лейбл с информацией о trappy circles
   * @param tr_lines_info: лейбл с информацией о trappy lines
   */
  void SetSettingsLabels(QLabel* targets_info, QLabel* hills_info,
                         QLabel* tr_circles_info, QLabel* tr_lines_info) {
    targets_label_.reset(targets_info);
    hills_label_.reset(hills_info);
    tr_circles_label_.reset(tr_circles_info);
    tr_lines_label_.reset(tr_lines_info);
  }

  /**
   * @brief устанавливает значение всех таблиц с информацией
   * @param hills_info: QTableWidget с информацией о hills
   * @param targets_info: QTableWidget с информацией о hills
   * @param tr_circles_info: QTableWidget с информацией о hills
   * @param tr_lines_info: QTableWidget с информацией о hills
   */
  void SetSettingsTables(QTableWidget* targets_info, QTableWidget* hills_info,
                         QTableWidget* tr_circles_info,
                         QTableWidget* tr_lines_info) {
    t_manager_.SetSettingsTables(targets_info, hills_info, tr_circles_info,
                                 tr_lines_info);
  }

  // @brief перерисовывает на полотне все объекты и обновляет данные
  void Redraw();

  /**
   * @brief удаляет объект на полотне по индексу объекта в его векторе
   * @param obj_type: тип объекта
   * @param index: индекс в его векторе
   */
  void Remove(gui::ObjectType obj_type, size_t index);

  // ----------------------   Target methods   ----------------------

  // for gui::Target
  void Add(gui::Target t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::Target> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<gui::Target> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<gui::Target> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::Target> vec) { manager_.Set(vec); }

  // for lib::Target
  void Add(lib::Target data) { manager_.Add(data); }
  void Add(std::initializer_list<lib::Target> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<lib::Target> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<lib::Target> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<lib::Target> vec) { manager_.Set(vec); }

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

  // for gui::Hill
  void Add(gui::Hill t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::Hill> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<gui::Hill> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<gui::Hill> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::Hill> vec) { manager_.Set(vec); }

  // for lib::Hill
  void Add(lib::Hill data) { manager_.Add(data); }
  void Add(std::initializer_list<lib::Hill> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<lib::Hill> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<lib::Hill> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<lib::Hill> vec) { manager_.Set(vec); }

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

  // for gui::TrappyCircle
  void Add(gui::TrappyCircle t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::TrappyCircle> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<gui::TrappyCircle> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<gui::TrappyCircle> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::TrappyCircle> vec) { manager_.Set(vec); }

  // for lib::TrappyCircle
  void Add(lib::TrappyCircle data) { manager_.Add(data); }
  void Add(std::initializer_list<lib::TrappyCircle> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<lib::TrappyCircle> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<lib::TrappyCircle> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<lib::TrappyCircle> vec) { manager_.Set(vec); }

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

  // for gui::TrappyLine
  void Add(const gui::TrappyLine& t) { manager_.Add(t); }
  void Add(std::initializer_list<gui::TrappyLine> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<gui::TrappyLine> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<gui::TrappyLine> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<gui::TrappyLine> vec) { manager_.Set(vec); }

  // for lib::TrappyLine
  void Add(lib::TrappyLine data) { manager_.Add(data); }
  void Add(std::initializer_list<lib::TrappyLine> init_list) {
    manager_.Add(init_list);
  }
  void Add(std::vector<lib::TrappyLine> vec) { manager_.Add(vec); }

  void Set(std::initializer_list<lib::TrappyLine> init_list) {
    manager_.Set(init_list);
  }
  void Set(std::vector<lib::TrappyLine> vec) { manager_.Set(vec); }

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
  // @brief обновляет данные в лейблах все объектов
  void UpdateInfoLabels();

  // @brief обновляет данные в таблицах всех объектов
  void UpdateTables();

  // vars

  // i love unique_ptr's, i love logic schemes
  std::unique_ptr<QCustomPlot> plot_;

  std::unique_ptr<QLabel> hills_label_{nullptr};
  std::unique_ptr<QLabel> targets_label_{nullptr};
  std::unique_ptr<QLabel> tr_circles_label_{nullptr};
  std::unique_ptr<QLabel> tr_lines_label_{nullptr};

  gui::DataManager manager_;
  TableManager t_manager_;

  // ~vars
};
