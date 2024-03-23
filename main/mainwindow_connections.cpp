#include "mainwindow.h"

// здесь описаны все соединения кнопок со слотами

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"

void MainWindow::AddTarget(double x, double y) {
  manager_.Add(gui::Target(x, y));
  manager_.Draw(PlotManager::ObjectType::Targets);
}

void MainWindow::on_pushButtonAddTarget_clicked() {
  AddTargetForm* atf = new AddTargetForm;
  atf->setWindowTitle("Add Target");
  atf->setWindowIcon(QIcon("../images/target.png"));
  atf->setModal(true);
  atf->show();
  connect(atf, &AddTargetForm::AddTarget, this, &MainWindow::AddTarget);
}

void MainWindow::AddTrappyCircle(double x, double y, double radius,
                                 QColor color) {
  manager_.Add(gui::TrappyCircle(x, y, radius, color));
  manager_.Draw(PlotManager::ObjectType::TrappyCircles);
}
void MainWindow::on_pushButtonAddTrappyCircle_clicked() {
  AddTrappyCircleForm* adf = new AddTrappyCircleForm;
  adf->setWindowTitle("Add Trappy Circle");
  adf->setWindowIcon(QIcon("../images/AA.png"));
  adf->setModal(true);
  adf->show();
  connect(adf, &AddTrappyCircleForm::AddTrappyCircle, this,
          &MainWindow::AddTrappyCircle);
}

void MainWindow::AddTrappyLine(double x1, double y1, double x2, double y2) {
  // на данный момент просто добавляем новые
  // точки при создании новой линии опасного перелета

  gui::Target t1(x1, y1);
  gui::Target t2(x2, y2);

  manager_.Add(t1);
  manager_.Add(t2);
  manager_.Draw(PlotManager::ObjectType::Targets);

  manager_.Add(gui::TrappyLine({t1, t2}));
  manager_.Draw(PlotManager::ObjectType::TrappyLines);
}
void MainWindow::on_pushButtonAddTrappyLine_clicked() {
  AddTrappyLineForm* adl = new AddTrappyLineForm;
  adl->setWindowTitle("Add Trappy Line");
  adl->setWindowIcon(QIcon("../images/enemy.png"));
  adl->setModal(true);
  adl->show();
  connect(adl, &AddTrappyLineForm::AddTrappyLine, this,
          &MainWindow::AddTrappyLine);
}
