#include "main/mainwindow.h"
// здесь описаны все соединения кнопок со слотами

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

// MARK: Add functions

void MainWindow::AddTarget(double x, double y) {
  manager_->Add(new gui::Target(x, y));
  area_->Redraw();
  t_connection_->UpdateTables();
}

void MainWindow::AddTrappyCircle(double x, double y, double radius) {
  manager_->Add(new gui::TrappyCircle(x, y, radius));
  area_->Redraw();
  t_connection_->UpdateTables();
}

void MainWindow::AddTrappyLine(double x1, double y1, double x2, double y2) {
  // на данный момент просто добавляем новые
  // точки при создании новой линии опасного перелета
  manager_->Add(new gui::Target(x1, y1));
  manager_->Add(new gui::Target(x2, y2));

  manager_->Add(new gui::TrappyLine(
      manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 2],
      manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 1]));

  area_->Redraw();
  t_connection_->UpdateTables();
}

void MainWindow::AddHill(std::vector<lib::Point> points) {
  manager_->Add(new gui::Hill(points));

  area_->Redraw();
  t_connection_->UpdateTables();
}

// MARK: Cursors buttons

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

// MARK: Actions trig.

void MainWindow::on_actionTarget_triggered() {
  DeleteLastAddedObject();

  AddTargetForm* atf = new AddTargetForm;
  atf->show();
  connect(atf, &AddTargetForm::AddTarget, this, &MainWindow::AddTarget);
}

void MainWindow::on_actionTrappy_Circle_triggered() {
  DeleteLastAddedObject();

  AddTrappyCircleForm* adf = new AddTrappyCircleForm;
  adf->show();
  connect(adf, &AddTrappyCircleForm::AddTrappyCircle, this,
          &MainWindow::AddTrappyCircle);
}

void MainWindow::on_actionTrappy_Line_triggered() {
  DeleteLastAddedObject();

  AddTrappyLineForm* adl = new AddTrappyLineForm;
  adl->show();
  connect(adl, &AddTrappyLineForm::AddTrappyLine, this,
          &MainWindow::AddTrappyLine);
}

void MainWindow::on_actionHill_triggered() {
  DeleteLastAddedObject();

  AddHillForm* adh = new AddHillForm;
  adh->show();
  connect(adh, &AddHillForm::AddHill, this, &MainWindow::AddHill);
}

// MARK: Extra connections

void MainWindow::on_pushButtonEditObjects_clicked() {
  DeleteLastAddedObject();

  ui->plotSettingsDockWidget->setVisible(true);
  on_actionBeautify_triggered();
}

void MainWindow::on_actionBeautify_triggered() {
  ui->plot->xAxis->setScaleRatio(ui->plot->yAxis, 1.0);
  ui->plot->replot();
}

// MARK: Json connections

// Вызов окна, которое сообщает об изменениях в файле
// и возвращает true, если окно было закрыто
bool MainWindow::OpenMessageWindow() {
  QString text =
      "Do you want save changes in file " + json_file_.GetFileName() + "?";
  int ret = QMessageBox::question(
      this, "Are you sure?", text,
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Save: {
      bool is_closed = on_actionSave_triggered();
      if (is_closed) return true;
      break;
    }

    case QMessageBox::Discard:
      break;

    case QMessageBox::Cancel:
    case QMessageBox::Close:
      return true;
      break;
  }

  return false;
}

// При закрытии приложения нужно проверить,
// есть ли изменения в текущем файле
void MainWindow::closeEvent(QCloseEvent* event) {
  DeleteLastAddedObject();

  bool is_closed = false;

  if (json_file_.IsExistsFile() && json_file_.IsChanged(manager_.get()))
    is_closed = OpenMessageWindow();

  else if (!json_file_.IsExistsFile() && (manager_->GetTargets().size() +
                                          manager_->GetTrappyCircles().size() +
                                          manager_->GetTrappyLines().size() +
                                          manager_->GetHills().size()) != 0) {
    is_closed = OpenMessageWindow();
  }

  if (is_closed)
    event->ignore();
  else
    event->accept();
}

// Кнопка "New"
void MainWindow::on_actionNew_triggered() {
  DeleteLastAddedObject();

  bool is_closed = false;

  if (json_file_.IsExistsFile() && json_file_.IsChanged(manager_.get()))
    is_closed = OpenMessageWindow();

  else if (!json_file_.IsExistsFile() && (manager_->GetTargets().size() +
                                          manager_->GetTrappyCircles().size() +
                                          manager_->GetTrappyLines().size() +
                                          manager_->GetHills().size()) != 0)
    is_closed = OpenMessageWindow();

  if (!is_closed) {
    manager_->Clear();
    json_file_.SetUntitledFile();
    area_->Redraw();
    t_connection_->UpdateTables();
  }
}

// Кнопка "Open"
void MainWindow::on_actionOpen_triggered() {
  DeleteLastAddedObject();

  bool is_closed = false;

  if (json_file_.IsExistsFile() && json_file_.IsChanged(manager_.get()))
    is_closed = OpenMessageWindow();

  else if (!json_file_.IsExistsFile() && (manager_->GetTargets().size() +
                                          manager_->GetTrappyCircles().size() +
                                          manager_->GetTrappyLines().size() +
                                          manager_->GetHills().size()) != 0)
    is_closed = OpenMessageWindow();

  if (!is_closed) {
    QString file_name = QFileDialog::getOpenFileName(
        this, tr("Open"), json_file_.GetParentPath(), tr("File (*.json)"));

    if (!file_name.isEmpty()) {
      QString old_filename = json_file_.GetFileName();

      try {
        json_file_.SetFile(file_name);
        manager_->Clear();
        json_file_.Open(manager_.get());
        area_->Redraw();
        t_connection_->UpdateTables();
      } catch (...) {
        QMessageBox::critical(this, "Damaged file", "Invalid format file!");
        json_file_.SetFile(old_filename);
      }
    }
  }
}

// Кнопка "Save"
// возвращает, было ли закрыто окно сохранения файла
bool MainWindow::on_actionSave_triggered() {
  DeleteLastAddedObject();

  if (!json_file_.IsExistsFile())
    return on_actionSave_as_triggered();
  else {
    json_file_.Save(manager_.get());
    return false;
  }
}

// Кнопка "Save as"
// возвращает, было ли закрыто окно сохранения файла
bool MainWindow::on_actionSave_as_triggered() {
  DeleteLastAddedObject();

  QString file_name = QFileDialog::getSaveFileName(
      this, tr("Save as"), json_file_.GetRelativePath(), tr("File (*.json)"));

  if (!file_name.isEmpty()) {
    json_file_.SetFile(file_name);
    json_file_.Save(manager_.get());
    return false;
  }
  return true;
}

// MARK: From table

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
