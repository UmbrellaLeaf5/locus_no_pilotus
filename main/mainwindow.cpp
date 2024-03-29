#include "mainwindow.h"

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"
// #include "icecream.hpp"  // IGNORE

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                            QCP::iSelectPlottables);
  manager_.SetPlot(ui->plot);

  {  // проверка функционала графических классов и менеджера

    gui::Target t_1(3, 4);
    gui::Target t_2(2, 1);
    gui::Target t_3(1, 1);

    manager_.Set({t_1, t_2, t_3});

    gui::TrappyLine tr{t_1, t_2};
    manager_.Add(tr);

    gui::TrappyCircle trc({1, 2}, 0.5);
    manager_.Add(trc);

    gui::Hill hill{{2, 3}, {3, 2}, {4, 4}};
    manager_.Add(hill);

    manager_.Add(gui::Hill(lib::Point(1, 4), 0.5, 7));

    manager_.Draw();
  }
}

MainWindow::~MainWindow() { delete ui; }
