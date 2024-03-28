#pragma once

#include <add_objects_forms/add_target_form.h>
#include <add_objects_forms/add_trappy_circle_form.h>
#include <add_objects_forms/add_trappy_line_form.h>
#include <plot_manager/plot_manager.h>

#include <QMainWindow>

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
  void on_pushButtonEditObjects_clicked();

  void on_actionTarget_triggered();
  void on_actionTrappy_Circle_triggered();
  void on_actionTrappy_Line_triggered();
  void on_actionHill_triggered();

 public slots:
  void AddTrappyCircle(double x, double y, double radius, QColor color);
  void AddTarget(double x, double y);
  void AddTrappyLine(double x1, double y1, double x2, double y2);

 private:
  PlotManager manager_;
  Ui::MainWindow* ui;
};
