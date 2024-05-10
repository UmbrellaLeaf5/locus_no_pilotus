#pragma once

// Qt libs:
#include <QMainWindow>

// autogen libs:
#include "./ui_mainwindow.h"

// our code libs:
#include "add_objects_forms/_forms.h"
#include "data_tools/_tools.h"
#include "gui_json_file/gui_json_file.h"

enum class CursorType {
  TargetCursor,
  TrCircleCursor,
  TrLineCursor,
  HillCursor,
  DefaultCursor
};

constexpr double max_scale = lib::max_coord / 2;
constexpr double min_scale = 10e-4;

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

  // Slots for files:
  bool on_actionSave_as_triggered();
  bool on_actionSave_triggered();
  void on_actionOpen_triggered();
  void on_actionNew_triggered();

  // Slots for interaction objects adding:
  void mousePressObjectsButton(QMouseEvent* mouse_event);
  void mousePressContextMenu(QMouseEvent* mouse_event);
  void mousePressRemoveObject();
  void DisconnectObject(gui::ObjectType obj_type);
  void closeEvent(QCloseEvent* event) override;
  void keyPressEvent(QKeyEvent* key_event) override;

  // Slots for Target:
  void on_addTargetPushButton_clicked();
  void on_actionTarget_triggered();

  // Slots for TrappyCircle:
  void on_addTrappyCirclePushButton_clicked();
  void on_actionTrappy_Circle_triggered();
  void mousePressSetRadiusFromPlot(QMouseEvent* mouse_event);
  void mouseMoveSetRadiusFromPlot(QMouseEvent* mouse_event);

  // Slots for TrappyLine:
  void on_addTrappyLinePushButton_clicked();
  void on_actionTrappy_Line_triggered();
  void on_actionHill_triggered();
  void mousePressSelectSecondTarget(QMouseEvent* mouse_event);

  // Slots for Hill:
  void on_addHillPushButton_clicked();
  void mousePressAddVertice(QMouseEvent* mouse_event);
  void mousePressDeleteLastVertice(QMouseEvent* mouse_event);
  void mouseMoveAddVertice(QMouseEvent* mouse_event);

  // Slots for Settings:
  void on_targetAddFromTablePushButton_clicked();
  void on_hillAddFromTablePushButton_clicked();
  void on_trappyCircleAddFromTablePushButton_clicked();
  void on_trappyLineAddFromTablePushButton_clicked();
  void on_editObjectsPushButton_clicked();

  // Extra slots:
  void on_actionBeautify_triggered();

  void on_xAxis_rangeChanged(QCPRange range);
  void on_yAxis_rangeChanged(QCPRange range);

  void on_drawTrajectoryPushButton_clicked() { area_->ReDrawTrajectory(); }
  void on_flyRobotPushButton_clicked() {}

 public slots:
  void AddTrappyCircle(double x, double y, double radius);
  void AddTarget(double x, double y);
  void AddTrappyLine(double x1, double y1, double x2, double y2);
  void AddHill(const std::vector<std::pair<double, double>>& points);

 private:
  Ui::MainWindow* ui;
  QTimer* timer;
  gui::Trajectory* trj;
  gui::FlyingRobot* robot;

  std::unique_ptr<data_tools::PlotArea> area_;
  std::unique_ptr<data_tools::DataManager> manager_;
  std::unique_ptr<data_tools::TablesConnection> t_connection_;

  GuiJsonFile json_file_;
  CursorType cursor_{CursorType::DefaultCursor};
  WhatObjectAddition what_obj_addition_{WhatObjectAddition::Nothing};

  bool OpenMessageWindow();
  gui::ObjectType GetObjType() const;
  void DeleteLastAddedObject();
};
