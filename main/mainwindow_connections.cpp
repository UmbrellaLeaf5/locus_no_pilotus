#include "mainwindow.h"

// здесь описаны все соединения кнопок со слотами

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"
// #include "icecream.hpp"  // IGNORE

void MainWindow::AddTarget(double x, double y) {
  area_.Add(gui::Target(x, y));
  area_.Draw(gui::ObjectType::Targets);
}

void MainWindow::on_pushButtonAddTarget_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/target.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_actionTarget_triggered() {
  AddTargetForm* atf = new AddTargetForm;
  atf->setWindowTitle("Add Target");
  atf->setWindowIcon(QIcon("../images/target.png"));
  atf->setModal(true);
  atf->show();
  connect(atf, &AddTargetForm::AddTarget, this, &MainWindow::AddTarget);
}

void MainWindow::AddTrappyCircle(double x, double y, double radius,
                                 QColor color) {
  area_.Add(gui::TrappyCircle(x, y, radius, color));
  area_.Draw(gui::ObjectType::TrappyCircles);
}
void MainWindow::on_pushButtonAddTrappyCircle_clicked() {
  ui->plot->setCursor(QCursor(
      QPixmap("../images/AA.png").scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_actionTrappy_Circle_triggered() {
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

  area_.Add(t1);
  area_.Add(t2);
  area_.Draw(gui::ObjectType::Targets);

  area_.Add(gui::TrappyLine({t1, t2}));
  area_.Draw(gui::ObjectType::TrappyLines);
}

void MainWindow::on_pushButtonAddTrappyLine_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/enemy.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_actionTrappy_Line_triggered() {
  AddTrappyLineForm* adl = new AddTrappyLineForm;
  adl->setWindowTitle("Add Trappy Line");
  adl->setWindowIcon(QIcon("../images/enemy.png"));
  adl->setModal(true);
  adl->show();
  connect(adl, &AddTrappyLineForm::AddTrappyLine, this,
          &MainWindow::AddTrappyLine);
}

void MainWindow::AddHill() {}

void MainWindow::on_actionHill_triggered() {}

void MainWindow::on_pushButtonAddHill_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/high_hills.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_pushButtonEditObjects_clicked() {
  ui->plotSettingsDockWidget->setVisible(true);
}

void MainWindow::on_plot_MousePressed() {
  ui->plot->setCursor(Qt::CrossCursor);
  ui->plot->replot();
}
