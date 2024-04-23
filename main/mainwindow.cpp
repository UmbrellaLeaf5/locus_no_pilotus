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

  connect(ui->plot, &QCustomPlot::mouseDoubleClick, this,
          &MainWindow::mousePressObjectsButton);

  area_->Setup(manager_.get());
  t_connection_->Setup(manager_.get(), area_.get());

  area_->SetPlot(ui->plot);

  t_connection_->SetSettingsTables(
      ui->targetInfoTableWidget, ui->hillInfoTableWidget,
      ui->trappyCircleInfoTableWidget, ui->trappyLineInfoTableWidget);

  t_connection_->SetRemoveButtons(
      ui->targetRemovePushButton, ui->hillRemovePushButton,
      ui->trappyCircleRemovePushButton, ui->trappyLineRemovePushButton);

  // Нужно для того, чтобы при открытии приложения менялось имя "Untitled"
  // файла, так как может быть такое, что пользователь уже создавал такие файлы
  json_file_.SetUntitledFile();
}

MainWindow::~MainWindow() { delete ui; }
