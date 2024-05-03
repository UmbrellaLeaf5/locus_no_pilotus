#include "main/mainwindow.h"

void ChecksValues(std::vector<std::string> values) {
  for (const auto& value : values) {
    bool is_dot = false;
    if (value.empty()) throw std::invalid_argument("The number is empty!");
    for (size_t i = 0; i < value.size(); i++) {
      switch (value[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          break;
        case '-':
          if (i > 0)
            throw std::invalid_argument(
                "A minus can only be at the beginning of a number!");
          break;
        case '.':
          if (is_dot)
            throw std::invalid_argument("A number can't have a second point!");
          else if (i == 0 || value[i - 1] == '-')
            throw std::invalid_argument("A number can't starts with a point!");
          is_dot = true;
          break;
        default:
          throw std::invalid_argument("Incorrect number!");
      }
    }
  }
}

void MainWindow::AddTarget(std::string x, std::string y) {
  try {
    ChecksValues({x, y});

    manager_->Add(new gui::Target(std::stod(x), std::stod(y)));
    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::Targets);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddTrappyCircle(std::string x, std::string y,
                                 std::string radius) {
  try {
    ChecksValues({x, y, radius});

    manager_->Add(
        new gui::TrappyCircle(std::stod(x), std::stod(y), std::stod(radius)));
    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::TrappyCircles);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddTrappyLine(std::string x1, std::string y1, std::string x2,
                               std::string y2) {
  try {
    ChecksValues({x1, y1, x2, y2});

    manager_->Add(new gui::Target(std::stod(x1), std::stod(y1)));
    manager_->Add(new gui::Target(std::stod(x2), std::stod(y2)));

    manager_->Add(new gui::TrappyLine(
        manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 2],
        manager_->GetTargetsPtrs()[manager_->GetTargets().size() - 1]));

    area_->Redraw();
    t_connection_->UpdateTable(gui::ObjectType::TrappyLines);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error!", e.what());
  }
}

void MainWindow::AddHill(
    std::vector<std::pair<std::string, std::string>> points) {
  try {
    std::vector<lib::Point> lib_points;
    for (const auto& point : points) {
      ChecksValues({point.first, point.second});
      lib_points.push_back({std::stod(point.first), std::stod(point.second)});
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
