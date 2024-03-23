#pragma once

#include <add_data_form.h>

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
  void on_pushButtonAddObject_1_clicked();

 public slots:
  void AddTrappyCircle(double x, double y, double radius, QColor color);

 private:
  Ui::MainWindow* ui;
  AddDataForm* adf;
};
