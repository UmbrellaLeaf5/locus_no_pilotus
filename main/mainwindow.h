#pragma once

#include <QMainWindow>

#include "add_objects_forms/add_hill_form.h"
#include "add_objects_forms/add_target_form.h"
#include "add_objects_forms/add_trappy_circle_form.h"
#include "add_objects_forms/add_trappy_line_form.h"
#include "data_tools/plot_area/plot_area.h"
#include "gui_json_file/gui_json_file.h"

enum class FileType { UntitledFile, UsualFile };

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

  void closeEvent(QCloseEvent* event) override;

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

  void on_plot_MousePressed();

  void on_actionBeautify_triggered();

  void on_actionSave_as_triggered();
  void on_actionOpen_triggered();

  void on_actionSave_triggered();

  void on_actionNew_triggered();

  void on_redrawPushButton_clicked();

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

  bool OpenMessageWindow(FileType file_type);
};
