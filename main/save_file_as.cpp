#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

#include "../lib/base.h"
#include "mainwindow.h"

void MainWindow::on_actionSave_as_triggered() {
  QString file_name = QFileDialog::getOpenFileName(this, tr("Save as"), "json",
                                                   tr("File (*.json)"));
  json json_file;
  QFile file;

  file.setFileName(file_name);

  if (file.open(QIODevice::WriteOnly)) {
    int id = 10001;

    QJsonArray targets_array = json_file.object().value("Targets").toArray();

    for (size_t i = 0; i < manager_.GetTargets().size(); i++) {
      QVariantMap target_map;

      gui::Target t = manager_.GetTargets()[i];

      target_map.insert("Id", id);
      target_map.insert("X", t.GetPoint().x);
      target_map.insert("Y", t.GetPoint().y);

      QJsonObject target_obj = QJsonObject::fromVariantMap(target_map);

      targets_array.append(target_obj);

      id++;
    }

    json_file.setArray(targets_array);

    file.write("{\n\"Targets\":" + json_file.toJson());

    id = 20001;

    QJsonArray trappy_circles_array =
        json_file.object().value("Trappy_Circles").toArray();

    for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++) {
      QVariantMap trappy_circle_map;

      gui::TrappyCircle tc = manager_.GetTrappyCircles()[i];

      trappy_circle_map.insert("Id", id);
      trappy_circle_map.insert("X", tc.GetCenter().x);
      trappy_circle_map.insert("Y", tc.GetCenter().y);
      trappy_circle_map.insert("R", tc.GetRadius());
      trappy_circle_map.insert("Color", tc.GetColor().name());

      QJsonObject trappy_circle_obj =
          QJsonObject::fromVariantMap(trappy_circle_map);

      trappy_circles_array.append(trappy_circle_obj);

      id++;
    }

    json_file.setArray(trappy_circles_array);

    file.write(",\n\"Trappy_Circles\":" + json_file.toJson());

    id = 30001;

    QJsonArray trappy_lines_array =
        json_file.object().value("trappy_lines").toArray();

    for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++) {
      QVariantMap trappy_line_map;

      gui::TrappyLine tl = manager_.GetTrappyLines()[i];
      lib::Target t1 = tl.GetTargets()[0];
      lib::Target t2 = tl.GetTargets()[1];

      trappy_line_map.insert("Id", id);
      trappy_line_map.insert("X1", t1.GetPoint().x);
      trappy_line_map.insert("Y1", t1.GetPoint().y);
      trappy_line_map.insert("X2", t2.GetPoint().x);
      trappy_line_map.insert("Y2", t2.GetPoint().y);

      QJsonObject trappy_line_obj =
          QJsonObject::fromVariantMap(trappy_line_map);

      trappy_lines_array.append(trappy_line_obj);

      id++;
    }

    json_file.setArray(trappy_lines_array);

    file.write(",\n\"Trappy_Lines\":" + json_file.toJson());

    id = 40001;

    QJsonArray hills_array = json_file.object().value("Hills").toArray();

    for (size_t i = 0; i < manager_.GetHills().size(); i++) {
      QVariantMap hill_map;

      hill_map.insert("Id", id);

      gui::Hill h = manager_.GetHills()[i];

      for (size_t i = 0; i < h.GetPoints().size(); i++) {
        lib::Point t = h.GetPoints()[i];
        hill_map.insert("X" + QString::number(i + 1), t.x);
        hill_map.insert("Y" + QString::number(i + 1), t.y);
      }

      QJsonObject hill_obj = QJsonObject::fromVariantMap(hill_map);

      hills_array.append(hill_obj);

      id++;
    }

    json_file.setArray(hills_array);

    file.write(",\n\"Hills\":" + json_file.toJson() + "}");

    file.close();
  }

  else
    QMessageBox::information(nullptr, "File error", "Can't open json file!");
}
