// header file:
#include "main/mainwindow.h"

void MainWindow::AddTarget(double x, double y) {
  try {
    manager_->Add(new gui::Target(x, y));
    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::Targets);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddTrappyCircle(double x, double y, double radius) {
  try {
    manager_->Add(new gui::TrappyCircle(x, y, radius));
    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::TrappyCircles);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddTrappyLine(double x1, double y1, double x2, double y2) {
  try {
    manager_->Add(new gui::Target(x1, y1));
    manager_->Add(new gui::Target(x2, y2));

    manager_->Add(new gui::TrappyLine(
        manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 2],
        manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 1]));

    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::TrappyLines);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddHill(const std::vector<std::pair<double, double>>& points) {
  try {
    std::vector<lib::Point> lib_points;
    for (const auto& point : points) {
      lib_points.push_back({point.first, point.second});
    }

    manager_->Add(new gui::Hill(lib_points));

    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::Hills);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

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
