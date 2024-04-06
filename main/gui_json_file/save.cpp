#include "gui_json_file.h"

void GuiJsonFile::Save(PlotArea& plot_area) {
  QJsonObject root;

  QJsonArray targets_array;
  QJsonArray trappy_circles_array;
  QJsonArray trappy_lines_array;
  QJsonArray hills_array;

  int id = 10001;

  for (size_t i = 0; i < plot_area.GetTargets().size(); i++) {
    targets_array.append(plot_area.GetTargets()[i].GetData().Save(id));
    id++;
  }
  root.insert("Targets", targets_array);

  id = 20001;

  for (size_t i = 0; i < plot_area.GetTrappyCircles().size(); i++) {
    trappy_circles_array.append(
        plot_area.GetTrappyCircles()[i].GetData().Save(id));
    id++;
  }
  root.insert("Trappy_Circles", trappy_circles_array);

  id = 30001;

  for (size_t i = 0; i < plot_area.GetTrappyLines().size(); i++) {
    trappy_lines_array.append(plot_area.GetTrappyLines()[i].GetData().Save(id));
    id++;
  }
  root.insert("Trappy_Lines", trappy_lines_array);

  id = 40001;

  for (size_t i = 0; i < plot_area.GetHills().size(); i++) {
    hills_array.append(plot_area.GetHills()[i].GetData().Save(id));
    id++;
  }
  root.insert("Hills", hills_array);

  QJsonDocument json_file(root);
  QString json_string = json_file.toJson(QJsonDocument::Indented);

  if (file_->open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream text_stream(file_);
    text_stream << json_string;
    file_->close();
  }
}
