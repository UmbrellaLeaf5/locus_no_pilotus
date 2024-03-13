#include "mainwindow.h"

#include "../gui/no_direct_fly_rule.h"
#include "../gui/target.h"
#include "../lib/target.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
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
}

MainWindow::~MainWindow() { delete ui; }
