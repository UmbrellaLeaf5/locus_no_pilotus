#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

#include "../lib/base.h"
#include "mainwindow.h"

void MainWindow::on_actionOpen_triggered() {
  QString file_name = QFileDialog::getOpenFileName(this, tr("Open"), "json",
                                                   tr("File (*.json)"));
  json json_file;
  QFile file;

  file.setFileName(file_name);

  if (file.open(QIODevice::ReadOnly | QFile::Text))
    json_file = QJsonDocument::fromJson(QByteArray(file.readAll()));
  else
    QMessageBox::information(nullptr, "File error", "Can't open json file!");

  QJsonObject root = json_file.object();

  QJsonValue json_targets = root.value("Targets");
  QJsonValue json_trappy_circles = root.value("Trappy_Circles");
  QJsonValue json_trappy_lines = root.value("Trappy_Lines");
  QJsonValue json_hills = root.value("Hills");

  if (json_targets.isArray()) {
    QJsonArray targets_array = json_targets.toArray();

    for (size_t i = 0; i < targets_array.size(); i++) {
      QJsonObject target_obj = targets_array.at(i).toObject();

      manager_.Add(gui::Target(target_obj.value("X").toDouble(),
                               target_obj.value("Y").toDouble()));
    }
  }

  if (json_trappy_circles.isArray()) {
    QJsonArray trappy_circles_array = json_trappy_circles.toArray();

    for (size_t i = 0; i < trappy_circles_array.size(); i++) {
      QJsonObject trappy_circle_obj = trappy_circles_array.at(i).toObject();

      manager_.Add(
          gui::TrappyCircle(trappy_circle_obj.value("X").toDouble(),
                            trappy_circle_obj.value("Y").toDouble(),
                            trappy_circle_obj.value("R").toDouble(),
                            trappy_circle_obj.value("Color").toString()));
    }
  }

  if (json_trappy_lines.isArray()) {
    QJsonArray trappy_lines_array = json_trappy_lines.toArray();

    for (size_t i = 0; i < trappy_lines_array.size(); i++) {
      QJsonObject trappy_line_obj = trappy_lines_array.at(i).toObject();

      double x1 = trappy_line_obj.value("X1").toDouble();
      double y1 = trappy_line_obj.value("Y1").toDouble();
      double x2 = trappy_line_obj.value("X2").toDouble();
      double y2 = trappy_line_obj.value("Y2").toDouble();

      gui::Target t1;
      gui::Target t2;

      for (auto t : manager_.GetTargets()) {
        if (x1 == t.GetPoint().x && y1 == t.GetPoint().y) {
          t1 = t;

        } else if (x2 == t.GetPoint().x && y2 == t.GetPoint().y) {
          t2 = t;
        }
      }

      gui::TrappyLine tl{t1, t2};
      manager_.Add(tl);
    }
  }

  if (json_hills.isArray()) {
    QJsonArray hills_array = json_hills.toArray();

    for (size_t i = 0; i < hills_array.size(); i++) {
      QJsonObject hill_obj = hills_array.at(i).toObject();

      std::vector<lib::Point> points;

      for (size_t j = 0; j < hill_obj.size() / 2; j++) {
        points.push_back(
            {hill_obj.value("X" + QString::number(j + 1)).toDouble(),
             hill_obj.value("Y" + QString::number(j + 1)).toDouble()});
      }

      manager_.Add(gui::Hill(points));
    }
  }

  manager_.Draw();
}
