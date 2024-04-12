#include "gui_json_file.h"

QJsonObject GuiJsonFile::LoadJson() {
  QString json_text = file_->readAll();
  QJsonDocument json_file = QJsonDocument::fromJson(json_text.toUtf8());
  return json_file.object();
}

bool GuiJsonFile::IsChanged(PlotArea& plot_area) {
  if (file_->open(QIODevice::ReadOnly | QFile::Text)) {
    QJsonObject root = LoadJson();

    QJsonArray json_targets = root["Targets"].toArray();
    QJsonArray json_trappy_circles = root["Trappy_Circles"].toArray();
    QJsonArray json_trappy_lines = root["Trappy_Lines"].toArray();
    QJsonArray json_hills = root["Hills"].toArray();

    for (size_t i = 0; i < plot_area.GetTargets().size(); i++) {
      lib::Target t = plot_area.GetTargets()[i].GetData();
      if (t.IsChanged(json_targets.at(i).toObject())) {
        file_->close();
        return true;
      }
    }

    for (size_t i = 0; i < plot_area.GetTrappyCircles().size(); i++) {
      lib::TrappyCircle tc = plot_area.GetTrappyCircles()[i].GetData();
      if (tc.IsChanged(json_trappy_circles.at(i).toObject())) {
        file_->close();
        return true;
      }
    }

    for (size_t i = 0; i < plot_area.GetTrappyLines().size(); i++) {
      lib::TrappyLine tl = plot_area.GetTrappyLines()[i].GetData();
      if (tl.IsChanged(json_trappy_lines.at(i).toObject())) {
        file_->close();
        return true;
      }
    }

    for (size_t i = 0; i < plot_area.GetHills().size(); i++) {
      lib::Hill h = plot_area.GetHills()[i].GetData();
      if (h.IsChanged(json_hills.at(i).toObject())) {
        file_->close();
        return true;
      }
    }

    file_->close();
    return false;
  }
}
