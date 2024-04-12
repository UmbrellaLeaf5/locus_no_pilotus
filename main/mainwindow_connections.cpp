#include "mainwindow.h"

// здесь описаны все соединения кнопок со слотами

#include "../gui/hill.h"
#include "../gui/target.h"
#include "../gui/trappy_circle.h"
#include "../gui/trappy_line.h"
#include "./ui_mainwindow.h"

void MainWindow::AddTarget(double x, double y) {
  area_.Add(gui::Target(x, y));
  area_.Redraw();
}

void MainWindow::AddTrappyCircle(double x, double y, double radius) {
  area_.Add(gui::TrappyCircle(x, y, radius));
  area_.Redraw();
}

void MainWindow::AddTrappyLine(double x1, double y1, double x2, double y2) {
  // на данный момент просто добавляем новые
  // точки при создании новой линии опасного перелета

  gui::Target t1(x1, y1);
  gui::Target t2(x2, y2);

  area_.Add(t1);
  area_.Add(t2);
  area_.Redraw();

  area_.Add(gui::TrappyLine({t1, t2}));
  area_.Redraw();
}

void MainWindow::AddHill(std::vector<lib::Point> points) {
  area_.Add(gui::Hill(points));
  area_.Redraw();
}

void MainWindow::on_pushButtonAddTarget_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/target.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_pushButtonAddTrappyCircle_clicked() {
  ui->plot->setCursor(QCursor(
      QPixmap("../images/AA.png").scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_pushButtonAddTrappyLine_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/enemy.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_pushButtonAddHill_clicked() {
  ui->plot->setCursor(QCursor(QPixmap("../images/high_hills.png")
                                  .scaled(QSize(24, 24), Qt::KeepAspectRatio)));
}

void MainWindow::on_actionTarget_triggered() {
  AddTargetForm* atf = new AddTargetForm;
  atf->show();
  connect(atf, &AddTargetForm::AddTarget, this, &MainWindow::AddTarget);
}

void MainWindow::on_actionTrappy_Circle_triggered() {
  AddTrappyCircleForm* adf = new AddTrappyCircleForm;
  adf->show();
  connect(adf, &AddTrappyCircleForm::AddTrappyCircle, this,
          &MainWindow::AddTrappyCircle);
}

void MainWindow::on_actionTrappy_Line_triggered() {
  AddTrappyLineForm* adl = new AddTrappyLineForm;
  adl->show();
  connect(adl, &AddTrappyLineForm::AddTrappyLine, this,
          &MainWindow::AddTrappyLine);
}

void MainWindow::on_actionHill_triggered() {
  AddHillForm* adh = new AddHillForm;
  adh->show();
  connect(adh, &AddHillForm::AddHill, this, &MainWindow::AddHill);
}

void MainWindow::on_pushButtonEditObjects_clicked() {
  ui->plotSettingsDockWidget->setVisible(true);
  on_actionBeautify_triggered();
}

void MainWindow::on_actionBeautify_triggered() {
  ui->plot->xAxis->setScaleRatio(ui->plot->yAxis, 1.0);
  ui->plot->replot();
}

void MainWindow::on_plot_MousePressed() {
  ui->plot->setCursor(Qt::CrossCursor);
  ui->plot->replot();
}

// Вызов окна, которое сообщает об изменениях в файле
// и возвращает true, если окно было закрыто
bool MainWindow::OpenMessageWindow(FileType file_type) {
  switch (file_type) {
    case FileType::UsualFile: {
      QString text =
          "Do you want save changes in file " + json_file_.GetFileName() + "?";
      int ret = QMessageBox::question(
          this, "Are you sure?", text,
          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

      switch (ret) {
        case QMessageBox::Save:
          json_file_.Save(area_);
          break;
        case QMessageBox::Discard:
          break;
        case QMessageBox::Cancel:
        case QMessageBox::Close:
          return true;
          break;
      }
      break;
    }
    case FileType::UntitledFile: {
      QString text = "Do you want save changes in file " +
                     json_file_.GetUntitledFile() + '?';
      int ret = QMessageBox::question(
          this, "Are you sure?", text,
          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      switch (ret) {
        case QMessageBox::Save:
          on_actionSave_as_triggered();
          break;
        case QMessageBox::Discard:
          break;
        case QMessageBox::Cancel:
        case QMessageBox::Close:
          return true;
          break;
      }
      break;
    }
  }
  area_.Clear();
  json_file_.Clear();
  return false;
}

// При закрытии приложения нужно проверить,
// есть ли изменения в текущем файле
void MainWindow::closeEvent(QCloseEvent* event) {
  bool is_closed = false;
  if (json_file_.IsExistsFile() && json_file_.IsChanged(area_))
    is_closed = OpenMessageWindow(FileType::UsualFile);
  else if (!json_file_.IsExistsFile() &&
           (area_.GetTargets().size() + area_.GetTrappyCircles().size() +
            area_.GetTrappyLines().size() + area_.GetHills().size()) != 0)
    is_closed = OpenMessageWindow(FileType::UntitledFile);
  if (is_closed)
    event->ignore();
  else
    event->accept();
}

// Кнопка "New"
void MainWindow::on_actionNew_triggered() {
  bool is_closed = false;
  if (json_file_.IsExistsFile() && json_file_.IsChanged(area_))
    is_closed = OpenMessageWindow(FileType::UsualFile);
  else if (!json_file_.IsExistsFile() &&
           (area_.GetTargets().size() + area_.GetTrappyCircles().size() +
            area_.GetTrappyLines().size() + area_.GetHills().size()) != 0)
    is_closed = OpenMessageWindow(FileType::UntitledFile);
}

// Кнопка "Open"
void MainWindow::on_actionOpen_triggered() {
  bool is_closed = false;
  if (json_file_.IsExistsFile() && json_file_.IsChanged(area_))
    is_closed = OpenMessageWindow(FileType::UsualFile);
  else if (!json_file_.IsExistsFile() &&
           (area_.GetTargets().size() + area_.GetTrappyCircles().size() +
            area_.GetTrappyLines().size() + area_.GetHills().size()) != 0)
    is_closed = OpenMessageWindow(FileType::UntitledFile);
  if (!is_closed) {
    QString file_name =
        QFileDialog::getOpenFileName(this, tr("Open"), "", tr("File (*.json)"));
    json_file_.SetFile(file_name);
    json_file_.Open(area_);
  }
}

// Кнопка "Save"
void MainWindow::on_actionSave_triggered() {
  if (!json_file_.IsExistsFile())
    on_actionSave_as_triggered();
  else
    json_file_.Save(area_);
}

// Кнопка "Save as"
void MainWindow::on_actionSave_as_triggered() {
  QString file_name = QFileDialog::getSaveFileName(
      this, tr("Save as"), json_file_.GetUntitledFile(), tr("File (*.json)"));
  json_file_.SetFile(file_name);
  json_file_.Save(area_);
}
