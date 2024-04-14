#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      area_(new data_tools::PlotArea),
      manager_(new data_tools::DataManager),
      t_connection_(new data_tools::TablesConnection) {
  ui->setupUi(this);
  ui->plotSettingsDockWidget->setVisible(false);

  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                            QCP::iSelectPlottables | QCP::iSelectItems);

  connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this,
          SLOT(on_plot_MousePressed()));

  area_->Setup(manager_.get(), t_connection_.get());
  t_connection_->Setup(manager_.get(), area_.get());

  area_->SetPlot(ui->plot);

  {  // проверка функционала графических классов и менеджера

    gui::Target t_1(3, 4);
    gui::Target t_2(2, 1);
    gui::Target t_3(1, 1);

    manager_->Set({t_1, t_2, t_3});

    gui::TrappyLine tr{t_1, t_2};
    manager_->Add(tr);

    gui::TrappyCircle trc({1, 2}, 0.5);
    manager_->Add(trc);

    manager_->Add(gui::Hill(lib::Point(1, 4), 0.5, 7));
  }

  t_connection_->SetSettingsTables(
      ui->targetInfoTableWidget, ui->hillInfoTableWidget,
      ui->trappyCircleInfoTableWidget, ui->trappyLineInfoTableWidget);

  area_->Redraw();
}

MainWindow::~MainWindow() { delete ui; }
