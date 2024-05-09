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

  std::vector<gui::Segment> segs{{{0, 0}, {5, 0}},
                                 {{5, 0}, {7, -2}, {7, 0}},
                                 {{7, -2}, {0, -5}},
                                 {{0, -5}, {0, 0}, {0, -2.5}}};
  trj = new gui::Trajectory(segs);
  trj->Draw(ui->plot);
  timer = new QTimer(this);
  robot = new gui::FlyingRobot(*trj);
  robot->Draw(ui->plot);
  connect(timer, &QTimer::timeout, this, &MainWindow::moveObject);
  timer->start(1000 / 360);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::moveObject() { robot->ReDraw(ui->plot); }
