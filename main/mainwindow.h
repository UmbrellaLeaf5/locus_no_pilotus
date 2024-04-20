#pragma once

#include <QMainWindow>

#include "./ui_mainwindow.h"
#include "add_objects_forms/add_hill_form.h"
#include "add_objects_forms/add_target_form.h"
#include "add_objects_forms/add_trappy_circle_form.h"
#include "add_objects_forms/add_trappy_line_form.h"
#include "data_tools/data_manager/data_manager.h"
#include "data_tools/plot_area/plot_area.h"
#include "data_tools/tables_connection/tables_connection.h"
#include "gui_json_file/gui_json_file.h"

enum class CursorType {
  TargetCursor,
  TrCircleCursor,
  TrLineCursor,
  HillCursor,
  DefaultCursor
};

enum class WhatObjectAddition { Nothing, Target, TrCircle, TrLine, Hill };

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionBeautify_triggered();

  // Слоты для Target
  void on_pushButtonAddTarget_clicked();
  void on_actionTarget_triggered();

  // Слоты для файлов
  bool on_actionSave_as_triggered();
  bool on_actionSave_triggered();
  void on_actionOpen_triggered();
  void on_actionNew_triggered();

  void mousePressObjectsButton(QMouseEvent* mouse_event);
  void DisconnectObject(gui::ObjectType obj_type);
  void closeEvent(QCloseEvent* event) override;
  void keyPressEvent(QKeyEvent* key_event) override;

  // Слоты для TrappyCircle
  void on_pushButtonAddTrappyCircle_clicked();
  void on_actionTrappy_Circle_triggered();
  void mousePressSetRadiusFromPlot(QMouseEvent* mouse_event) {
    DisconnectObject(gui::ObjectType::TrappyCircles);
    what_obj_addition_ = WhatObjectAddition::Nothing;
  }
  void mouseMoveSetRadiusFromPlot(QMouseEvent* mouse_event);

  // Слот для  TrappyLine
  void on_pushButtonAddTrappyLine_clicked();
  void on_actionTrappy_Line_triggered();
  void on_actionHill_triggered();
  void mousePressSelectSecondTarget(QMouseEvent* mouse_event);

  // Слотs для Hill
  void on_pushButtonAddHill_clicked();
  void mousePressAddVertice(QMouseEvent* mouse_event);

  // Слоты для Settings
  void on_targetAddFromTablePushButton_clicked();
  void on_hillAddFromTablePushButton_clicked();
  void on_trappyCircleAddFromTablePushButton_clicked();
  void on_trappyLineAddFromTablePushButton_clicked();
  void on_pushButtonEditObjects_clicked();

 public slots:
  void AddTrappyCircle(double x, double y, double radius);
  void AddTarget(double x, double y);
  void AddTrappyLine(double x1, double y1, double x2, double y2);
  void AddHill(std::vector<lib::Point> points);

 private:
  std::unique_ptr<data_tools::PlotArea> area_;
  std::unique_ptr<data_tools::DataManager> manager_;
  std::unique_ptr<data_tools::TablesConnection> t_connection_;

  Ui::MainWindow* ui;
  GuiJsonFile json_file_;
  CursorType cursor_ = CursorType::DefaultCursor;
  WhatObjectAddition what_obj_addition_ = WhatObjectAddition::Nothing;

  bool OpenMessageWindow();
  gui::ObjectType GetObjType(CursorType cursor_type);
  void DeleteLastAddedObject();
};
