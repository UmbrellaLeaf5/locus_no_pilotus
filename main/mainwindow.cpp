#include "mainwindow.h"

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  manager.SetPlot(ui->plot);

  gui::Target t_1(3, 4);
  gui::Target t_2(2, 1);
  gui::Target t_3(1, 1);

  manager.Set({t_1, t_2, t_3});

  gui::TrappyLine tr{t_1, t_2};
  manager.Add(tr);

  gui::TrappyCircle trc({1, 2}, 50);
  manager.Add(trc);

  gui::Hill hill{{2, 3}, {3, 2}, {4, 4}};
  manager.Add(hill);

  manager.Draw();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::AddTarget(double x, double y) {
  manager.Add(gui::Target(x, y));
  manager.Draw(PlotManager::ObjectType::Targets);
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
  manager.Add(gui::TrappyCircle(x, y, radius, color));
  manager.Draw(PlotManager::ObjectType::TrappyCircles);
}

void MainWindow::on_pushButtonAddObject_1_clicked() {
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

  manager.Add(t1);
  manager.Add(t2);
  manager.Draw(PlotManager::ObjectType::Targets);

  manager.Add(gui::TrappyLine({t1, t2}));
  manager.Draw(PlotManager::ObjectType::TrappyLines);
}

void MainWindow::on_pushButtonAddObject_2_clicked() {
  AddTrappyLineForm* adl = new AddTrappyLineForm;
  adl->setWindowTitle("Add Trappy Line");
  adl->setWindowIcon(QIcon("../images/enemy.png"));
  adl->setModal(true);
  adl->show();
  connect(adl, &AddTrappyLineForm::AddTrappyLine, this,
          &MainWindow::AddTrappyLine);
}
