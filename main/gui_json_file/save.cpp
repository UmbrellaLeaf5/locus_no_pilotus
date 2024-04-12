#include "gui_json_file.h"

void GuiJsonFile::Save(PlotArea& plot_area) {
  if (file_->fileName().indexOf("Untitled") != -1) {
    QString file_name = file_->fileName();
    QString old_untitled = "";
    for (size_t i = file_name.indexOf("Untitled"); i < file_name.size(); i++) {
      old_untitled += file_name[i];
    }
    ChangeUntitled(old_untitled);
  }

  QJsonObject root;

  QJsonArray targets_array;
  QJsonArray trappy_circles_array;
  QJsonArray trappy_lines_array;
  QJsonArray hills_array;

  int add_to_id = 10000;

  for (size_t i = 0; i < plot_area.GetTargets().size(); i++) {
    int id = add_to_id + plot_area.GetTargets()[i].GetPlottableIndex();
    targets_array.append(plot_area.GetTargets()[i].GetData().Save(id));
  }
  root.insert("Targets", targets_array);

  add_to_id = 20000;

  for (size_t i = 0; i < plot_area.GetTrappyCircles().size(); i++) {
    int id = add_to_id + plot_area.GetTrappyCircles()[i].GetItemIndex();
    trappy_circles_array.append(
        plot_area.GetTrappyCircles()[i].GetData().Save(id));
  }
  root.insert("Trappy_Circles", trappy_circles_array);

  add_to_id = 30000;

  for (size_t i = 0; i < plot_area.GetTrappyLines().size(); i++) {
    int id = add_to_id + plot_area.GetTrappyLines()[i].GetPlottableIndex();
    trappy_lines_array.append(plot_area.GetTrappyLines()[i].GetData().Save(id));
  }
  root.insert("Trappy_Lines", trappy_lines_array);

  add_to_id = 40000;

  for (size_t i = 0; i < plot_area.GetHills().size(); i++) {
    int id = add_to_id + plot_area.GetHills()[i].GetPlottableIndex();
    hills_array.append(plot_area.GetHills()[i].GetData().Save(id));
  }
  root.insert("Hills", hills_array);

  QJsonDocument json_file(root);
  QString json_string = json_file.toJson(QJsonDocument::Indented);

  file_->open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream text_stream(file_);
  text_stream << json_string;
  file_->close();
}
