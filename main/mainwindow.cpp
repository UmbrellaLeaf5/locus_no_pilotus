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
  manager_->Setup(area_.get(), t_connection_.get());

  area_->SetPlot(ui->plot);

  // нынче для проверки функционала файл открывают

  t_connection_->SetSettingsTables(
      ui->targetInfoTableWidget, ui->hillInfoTableWidget,
      ui->trappyCircleInfoTableWidget, ui->trappyLineInfoTableWidget);

  area_->Redraw();
}

MainWindow::~MainWindow() { delete ui; }
