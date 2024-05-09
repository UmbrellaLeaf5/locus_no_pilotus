// header file:
#include "mainwindow.h"

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

  connect(ui->plot, &QCustomPlot::mousePress, this,
          &MainWindow::mousePressContextMenu);

  connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
          SLOT(on_xAxis_rangeChanged(QCPRange)));

  connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
          SLOT(on_yAxis_rangeChanged(QCPRange)));

  area_->Setup(manager_.get());
  t_connection_->Setup(manager_.get(), area_.get());

  area_->SetPlot(ui->plot);

  t_connection_->SetSettingsTables(
      ui->targetInfoTableWidget, ui->hillInfoTableWidget,
      ui->trappyCircleInfoTableWidget, ui->trappyLineInfoTableWidget);

  t_connection_->SetRemoveButtons(
      ui->targetRemovePushButton, ui->hillRemovePushButton,
      ui->trappyCircleRemovePushButton, ui->trappyLineRemovePushButton);

  json_file_.SetUntitledFile();
}

MainWindow::~MainWindow() { delete ui; }
