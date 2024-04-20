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
  void on_pushButtonAddTarget_clicked();
  void on_pushButtonAddTrappyCircle_clicked();
  void on_pushButtonAddTrappyLine_clicked();
  void on_pushButtonAddHill_clicked();

  void on_pushButtonEditObjects_clicked();

  void on_actionTarget_triggered();
  void on_actionTrappy_Circle_triggered();
  void on_actionTrappy_Line_triggered();
  void on_actionHill_triggered();

  void on_actionBeautify_triggered();

  bool on_actionSave_as_triggered();
  bool on_actionSave_triggered();

  void on_actionOpen_triggered();
  void on_actionNew_triggered();

  void mousePressObjectsButton(QMouseEvent* mouse_event);
  void DisconnectObject(gui::ObjectType obj_type);
  void mousePressDiscard(QMouseEvent* mouse_event);
  void closeEvent(QCloseEvent* event) override;

  // Слоты для TrappyCircle
  void mousePressSetRadiusFromPlot(QMouseEvent* mouse_event) {
    DisconnectObject(gui::ObjectType::TrappyCircles);
  }
  void mousePressDiscardTrappyCircle(QMouseEvent* mouse_event);
  void mouseMoveSetRadiusFromPlot(QMouseEvent* mouse_event);

  // Слоты для  TrappyLine
  void mousePressSelectSecondTarget(QMouseEvent* mouse_event);
  void mousePressDiscardTrappyLine(QMouseEvent* mouse_event);

  // Слоты для Hill
  void mousePressAddVertice(QMouseEvent* mouse_event);
  void mousePressDiscardHill(QMouseEvent* mouse_event);

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

  bool OpenMessageWindow();
};
