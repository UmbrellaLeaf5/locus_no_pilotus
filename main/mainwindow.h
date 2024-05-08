#pragma once

#include <QMainWindow>

#include "./ui_mainwindow.h"
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
  void on_pushButtonAddTarget_clicked();
  void on_actionTarget_triggered();

  // Slots for TrappyCircle:
  void on_pushButtonAddTrappyCircle_clicked();
  void on_actionTrappy_Circle_triggered();
  void mousePressSetRadiusFromPlot(QMouseEvent* mouse_event);
  void mouseMoveSetRadiusFromPlot(QMouseEvent* mouse_event);

  // Slots for TrappyLine:
  void on_pushButtonAddTrappyLine_clicked();
  void on_actionTrappy_Line_triggered();
  void on_actionHill_triggered();
  void mousePressSelectSecondTarget(QMouseEvent* mouse_event);

  // Slots for Hill:
  void on_pushButtonAddHill_clicked();
  void mousePressAddVertice(QMouseEvent* mouse_event);
  void mousePressDeleteLastVertice(QMouseEvent* mouse_event);
  void mouseMoveAddVertice(QMouseEvent* mouse_event);

  // Slots for Settings:
  void on_targetAddFromTablePushButton_clicked();
  void on_hillAddFromTablePushButton_clicked();
  void on_trappyCircleAddFromTablePushButton_clicked();
  void on_trappyLineAddFromTablePushButton_clicked();
  void on_pushButtonEditObjects_clicked();

  // Extra slots:
  void on_actionBeautify_triggered();

  void on_xAxis_rangeChanged(QCPRange range);
  void on_yAxis_rangeChanged(QCPRange range);

 public slots:
  void AddTrappyCircle(std::string x, std::string y, std::string radius);
  void AddTarget(std::string x, std::string y);
  void AddTrappyLine(std::string x1, std::string y1, std::string x2,
                     std::string y2);
  void AddHill(std::vector<std::pair<std::string, std::string>> points);

 private:
  Ui::MainWindow* ui;

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
