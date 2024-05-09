// header file:
#include "gui_json_file.h"

void GuiJsonFile::Save(data_tools::DataManager* manager) {
  QJsonObject root;

  QJsonArray targets_array;
  QJsonArray trappy_circles_array;
  QJsonArray trappy_lines_array;
  QJsonArray hills_array;

  for (size_t i = 0; i < manager->GetTargets().size(); i++)
    targets_array.append(manager->GetTargets()[i].GetData().GetJsonInfo());
  root.insert("Targets", targets_array);

  for (size_t i = 0; i < manager->GetTrappyCircles().size(); i++)
    trappy_circles_array.append(
        manager->GetTrappyCircles()[i].GetData().GetJsonInfo());
  root.insert("Trappy_Circles", trappy_circles_array);

  for (size_t i = 0; i < manager->GetTrappyLines().size(); i++)
    trappy_lines_array.append(
        manager->GetTrappyLines()[i].GetData().GetJsonInfo());
  root.insert("Trappy_Lines", trappy_lines_array);

  for (size_t i = 0; i < manager->GetHills().size(); i++)
    hills_array.append(manager->GetHills()[i].GetData().GetJsonInfo());
  root.insert("Hills", hills_array);

  QJsonDocument json_file(root);
  QString json_string = json_file.toJson(QJsonDocument::Indented);

  file_->open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream text_stream(file_);
  text_stream << json_string;
  file_->close();
}
