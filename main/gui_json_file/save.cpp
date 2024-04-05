#include "gui_json_file.h"

void GuiJsonFile::WriteFile(std::vector<QJsonArray> arr) {
  json_file_->setArray(arr[0]);
  file_->write("{\n\"Targets\":" + json_file_->toJson());

  json_file_->setArray(arr[1]);
  file_->write(",\n\"Trappy_Circles\":" + json_file_->toJson());

  json_file_->setArray(arr[2]);
  file_->write(",\n\"Trappy_Lines\":" + json_file_->toJson());

  json_file_->setArray(arr[3]);
  file_->write(",\n\"Hills\":" + json_file_->toJson() + "}");

  file_->close();
}
void GuiJsonFile::Save(PlotArea& plot_area) {
  if (file_->open(QIODevice::WriteOnly)) {
    int id = 10001;

    std::vector<QJsonArray> arr;

    QJsonArray targets_array = json_file_->object().value("Targets").toArray();
    QJsonArray trappy_circles_array =
        json_file_->object().value("Trappy_Circles").toArray();
    QJsonArray trappy_lines_array =
        json_file_->object().value("Trappy_Lines").toArray();
    QJsonArray hills_array = json_file_->object().value("Hills").toArray();

    for (size_t i = 0; i < plot_area.GetTargets().size(); i++) {
      targets_array.append(plot_area.GetTargets()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(targets_array);

    id = 20001;

    for (size_t i = 0; i < plot_area.GetTrappyCircles().size(); i++) {
      trappy_circles_array.append(
          plot_area.GetTrappyCircles()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(trappy_circles_array);

    id = 30001;

    for (size_t i = 0; i < plot_area.GetTrappyLines().size(); i++) {
      trappy_lines_array.append(
          plot_area.GetTrappyLines()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(trappy_lines_array);

    id = 40001;

    for (size_t i = 0; i < plot_area.GetHills().size(); i++) {
      hills_array.append(plot_area.GetHills()[i].GetData().Save(id));
      id++;
    }
    arr.push_back(hills_array);

    WriteFile(arr);
  }
}
