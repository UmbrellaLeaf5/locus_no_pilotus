#include "mainwindow.h"

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                            QCP::iSelectPlottables | QCP::iSelectItems);

  connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this,
          SLOT(on_plot_MousePressed()));

  area_.SetPlot(ui->plot);

  area_.SetSettingsLabels(ui->targetInfoLabel, ui->hillInfoLabel,
                          ui->trappyCircleInfoLabel, ui->trappyLineInfoLabel);

  area_.SetSettingsTables(ui->targetInfoTableWidget, ui->hillInfoTableWidget,
                          ui->trappyCircleInfoTableWidget,
                          ui->trappyLineInfoTableWidget);

  ui->plotSettingsDockWidget->setVisible(false);

  {  // проверка функционала графических классов и менеджера

    gui::Target t_1(3, 4);
    gui::Target t_2(2, 1);
    gui::Target t_3(1, 1);

    area_.Set({t_1, t_2, t_3});

    gui::TrappyLine tr{t_1, t_2};
    area_.Add(tr);

    gui::TrappyCircle trc({1, 2}, 0.5);
    area_.Add(trc);

    area_.Add(gui::Hill(lib::Point(1, 4), 0.5, 7));

    area_.Redraw();

    // area_.Remove(gui::GuiObjType::Targets, 0);
  }
}

MainWindow::~MainWindow() { delete ui; }
