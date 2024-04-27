#include "main/mainwindow.h"

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

  if (is_closed) return;

  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open"), json_file_.GetParentPath(), tr("File (*.json)"));

  if (file_name.isEmpty()) return;

  QString old_filename = json_file_.GetFileName();

  try {
    json_file_.SetFile(file_name);
    manager_->Clear();
    json_file_.Open(manager_.get());
    area_->Redraw();
    t_connection_->UpdateTables();

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());

    json_file_.SetFile(old_filename);
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