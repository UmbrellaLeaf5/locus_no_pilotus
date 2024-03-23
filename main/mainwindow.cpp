#include "mainwindow.h"

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  gui::Target t_1(3, 4);
  gui::Target t_2(2, 1);
  gui::Target t_3(1, 1);

  t_1.Draw(ui->plot);
  t_2.Draw(ui->plot);
  t_3.Draw(ui->plot);

  gui::TrappyLine tr{t_1, t_2};
  tr.Draw(ui->plot);

  gui::TrappyCircle trc({1, 2}, 50);
  gui::Hill hill{{2, 3}, {3, 2}, {4, 4}};

  trc.Draw(ui->plot);
  hill.Draw(ui->plot);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButtonAddTarget_clicked() {
  AddTargetForm* atf = new AddTargetForm;
  atf->setWindowTitle("Add Target");
  atf->setWindowIcon(QIcon("../images/target.png"));
  atf->setModal(true);
  atf->show();
  connect(atf, &AddTargetForm::AddTarget, this, &MainWindow::AddTarget);
}

void MainWindow::AddTarget(double x, double y) {
  gui::Target t(x, y);
  t.Draw(ui->plot);
  ui->plot->replot();
}

void MainWindow::on_pushButtonAddObject_1_clicked() {
  AddDataForm* adf = new AddDataForm;
  adf->setWindowTitle("Add Trappy Circle");
  adf->setWindowIcon(QIcon("../images/AA.png"));
  adf->setModal(true);
  adf->show();
  connect(adf, &AddDataForm::AddTrappyCircle, this,
          &MainWindow::AddTrappyCircle);
}

void MainWindow::AddTrappyCircle(double x, double y, double radius,
                                 QColor color) {
  gui::TrappyCircle trc(x, y, radius, color);
  trc.Draw(ui->plot);
  ui->plot->replot();
}
