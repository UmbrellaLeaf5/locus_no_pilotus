#include "mainwindow.h"

#include "../gui/target.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  gui::Target t(2, 5);
  t.Draw(ui->plot);
}

MainWindow::~MainWindow() { delete ui; }
