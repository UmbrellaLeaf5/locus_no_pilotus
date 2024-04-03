#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

#include "../../lib/base.h"
#include "mainwindow.h"

void WriteFile(QFile &file, json json_file, std::vector<QJsonArray> arr) {
  json_file.setArray(arr[0]);
  file.write("{\n\"Targets\":" + json_file.toJson());

  json_file.setArray(arr[1]);
  file.write(",\n\"Trappy_Circles\":" + json_file.toJson());

  json_file.setArray(arr[2]);
  file.write(",\n\"Trappy_Lines\":" + json_file.toJson());

  json_file.setArray(arr[3]);
  file.write(",\n\"Hills\":" + json_file.toJson() + "}");

  file.close();
}

void MainWindow::on_actionSave_as_triggered() {
  QString file_name = QFileDialog::getSaveFileName(this, tr("Save as"), "json",
                                                   tr("File (*.json)"));
  json json_file;
  QFile file;

  file.setFileName(file_name);

  if (file.open(QIODevice::WriteOnly)) {
    int id = 10001;

    std::vector<QJsonArray> arr;

    QJsonArray targets_array = json_file.object().value("Targets").toArray();
    QJsonArray trappy_circles_array =
        json_file.object().value("Trappy_Circles").toArray();
    QJsonArray trappy_lines_array =
        json_file.object().value("Trappy_Lines").toArray();
    QJsonArray hills_array = json_file.object().value("Hills").toArray();

    for (size_t i = 0; i < manager_.GetTargets().size(); i++) {
      targets_array.append(manager_.GetTargets()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(targets_array);

    id = 20001;

    for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++) {
      trappy_circles_array.append(
          manager_.GetTrappyCircles()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(trappy_circles_array);

    id = 30001;

    for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++) {
      trappy_lines_array.append(
          manager_.GetTrappyLines()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(trappy_lines_array);

    id = 40001;

    for (size_t i = 0; i < manager_.GetHills().size(); i++) {
      hills_array.append(manager_.GetHills()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(hills_array);

    WriteFile(file, json_file, arr);
  }
}
