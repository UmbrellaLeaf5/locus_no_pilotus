// header file:
#include "main/mainwindow.h"

void MainWindow::StopRobot() {
  if (is_robot_flying_) {
    disconnect(timer_, &QTimer::timeout, this, &MainWindow::moveRobot);
    timer_->stop();
    is_robot_flying_ = false;

    ui->flyRobotPushButton->setIcon(QPixmap("../images/play_triangle.png"));
    area_->ReDraw();
    if (is_drown_trajectory_) area_->ReDrawTrajectory();
    area_->GetRobot()->SetTrajectory(nullptr);
    ui->plot->replot();

    ui->editObjectsPushButton->setEnabled(true);
  }
}

void MainWindow::FlyRobot() {
  if (!is_robot_flying_) {
    connect(timer_, &QTimer::timeout, this, &MainWindow::moveRobot);
    timer_->start(5);
    is_robot_flying_ = true;

    ui->flyRobotPushButton->setIcon(QPixmap("../images/stop_square.png"));

    if (!area_->GetRobot()->GetTrajectory())
      area_->GetRobot()->SetTrajectory(area_->GetTrajectory());

    area_->GetRobot()->Draw(ui->plot);
    ui->plot->replot();

    ui->plotSettingsDockWidget->setVisible(false);
    ui->editObjectsPushButton->setEnabled(false);
  }
}

void MainWindow::CalcTrajectory() {
  is_drown_trajectory_ = true;

  area_->ReDrawTrajectory();

  if (area_->TrajectorySize()) ui->calcTrajectoryPushButton->setEnabled(false);

  if (area_->TrajectorySize() && !ui->plotSettingsDockWidget->isVisible())
    ui->flyRobotPushButton->setEnabled(true);
}

void MainWindow::DeCalcTrajectory() {
  is_drown_trajectory_ = false;

  area_->ClearTrajectory();

  ui->calcTrajectoryPushButton->setEnabled(true);

  ui->flyRobotPushButton->setEnabled(false);

  if (is_robot_flying_) StopRobot();
}

void MainWindow::on_calcTrajectoryPushButton_clicked() {
  DeleteLastAddedObject();
  manager_->RemoveAllDuplicates();
  t_connection_->UpdateTables();
  area_->ReDraw();

  CalcTrajectory();
}

void MainWindow::on_flyRobotPushButton_clicked() {
  try {
    if (is_robot_flying_)
      StopRobot();
    else
      FlyRobot();

  } catch (const std::exception& e) {
    QMessageBox::warning(this, "Cannot add Robot!", e.what());
  }
}
