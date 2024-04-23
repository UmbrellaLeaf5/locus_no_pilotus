#include "gui_json_file.h"

void GuiJsonFile::Save(data_tools::DataManager* manager) {
  QJsonObject root;

  QJsonArray targets_array;
  QJsonArray trappy_circles_array;
  QJsonArray trappy_lines_array;
  QJsonArray hills_array;

  int add_to_id = 10000;

  for (size_t i = 0; i < manager->GetTargets().size(); i++) {
    int id = add_to_id + manager->GetTargets()[i].GetIndexOnPlot();
    targets_array.append(manager->GetTargets()[i].GetData().GetJsonInfo(id));
  }
  root.insert("Targets", targets_array);

  add_to_id = 20000;

  for (size_t i = 0; i < manager->GetTrappyCircles().size(); i++) {
    int id = add_to_id + manager->GetTrappyCircles()[i].GetItemIndex();
    trappy_circles_array.append(
        manager->GetTrappyCircles()[i].GetData().GetJsonInfo(id));
  }
  root.insert("Trappy_Circles", trappy_circles_array);

  add_to_id = 30000;

  for (size_t i = 0; i < manager->GetTrappyLines().size(); i++) {
    int id = add_to_id + manager->GetTrappyLines()[i].GetIndexOnPlot();
    trappy_lines_array.append(
        manager->GetTrappyLines()[i].GetData().GetJsonInfo(id));
  }
  root.insert("Trappy_Lines", trappy_lines_array);

  add_to_id = 40000;

  for (size_t i = 0; i < manager->GetHills().size(); i++) {
    int id = add_to_id + manager->GetHills()[i].GetIndexOnPlot();
    hills_array.append(manager->GetHills()[i].GetData().GetJsonInfo(id));
  }
  root.insert("Hills", hills_array);

  QJsonDocument json_file(root);
  QString json_string = json_file.toJson(QJsonDocument::Indented);

  file_->open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream text_stream(file_);
  text_stream << json_string;
  file_->close();
}
