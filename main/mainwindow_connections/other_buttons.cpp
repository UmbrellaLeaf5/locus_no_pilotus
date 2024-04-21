#include "main/mainwindow.h"

gui::ObjectType MainWindow::GetObjType() {
  switch (cursor_) {
    case CursorType::TrCircleCursor:
      return gui::ObjectType::TrappyCircles;
    case CursorType::TrLineCursor:
      return gui::ObjectType::TrappyLines;
    case CursorType::HillCursor:
      return gui::ObjectType::Hills;
    default:
      return gui::ObjectType::Targets;
  }
}

void MainWindow::on_pushButtonAddTarget_clicked() {
  DeleteLastAddedObject();

  ui->plot->setCursor(QCursor(QPixmap("../images/target.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
  cursor_ = CursorType::TargetCursor;
}

void MainWindow::on_pushButtonAddTrappyCircle_clicked() {
  DeleteLastAddedObject();

  ui->plot->setCursor(QCursor(
      QPixmap("../images/AA.png").scaled(QSize(24, 24), Qt::KeepAspectRatio)));
  cursor_ = CursorType::TrCircleCursor;
}

void MainWindow::on_pushButtonAddTrappyLine_clicked() {
  DeleteLastAddedObject();

  ui->plot->setCursor(QCursor(QPixmap("../images/enemy.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
  cursor_ = CursorType::TrLineCursor;
}

void MainWindow::on_pushButtonAddHill_clicked() {
  DeleteLastAddedObject();

  ui->plot->setCursor(QCursor(QPixmap("../images/high_hills.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
  cursor_ = CursorType::HillCursor;
}

void MainWindow::on_pushButtonEditObjects_clicked() {
  DeleteLastAddedObject();

  ui->plotSettingsDockWidget->setVisible(true);
  on_actionBeautify_triggered();
}

void MainWindow::on_actionBeautify_triggered() {
  ui->plot->xAxis->setScaleRatio(ui->plot->yAxis, 1.0);
  ui->plot->replot();
}

void MainWindow::on_targetAddFromTablePushButton_clicked() {
  on_actionTarget_triggered();
}

void MainWindow::on_hillAddFromTablePushButton_clicked() {
  on_actionHill_triggered();
}

void MainWindow::on_trappyCircleAddFromTablePushButton_clicked() {
  on_actionTrappy_Circle_triggered();
}

void MainWindow::on_trappyLineAddFromTablePushButton_clicked() {
  on_actionTrappy_Line_triggered();
}
