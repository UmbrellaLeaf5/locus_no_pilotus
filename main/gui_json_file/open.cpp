#include "gui_json_file.h"

std::vector<lib::Target> GetTargetsFromFile(QJsonArray arr,
                                            PlotArea& plot_area) {
  std::vector<lib::Target> targets;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Target t;
    t.Load(arr.at(i).toObject());
    targets.push_back(t);
  }
  return targets;
}

std::vector<lib::TrappyCircle> GetTrappyCirclesFromFile(QJsonArray arr,
                                                        PlotArea& plot_area) {
  std::vector<lib::TrappyCircle> trappy_circles;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyCircle tc;
    tc.Load(arr.at(i).toObject());
    trappy_circles.push_back(tc);
  }
  return trappy_circles;
}

std::vector<lib::TrappyLine> GetTrappyLinesFromFile(QJsonArray arr,
                                                    PlotArea& plot_area) {
  std::vector<lib::TrappyLine> trappy_lines;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyLine tl;
    tl.Load(arr.at(i).toObject());
    trappy_lines.push_back(tl);
  }
  return trappy_lines;
}

std::vector<lib::Hill> GetHillsFromFile(QJsonArray arr, PlotArea& plot_area) {
  std::vector<lib::Hill> hills;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Hill h;
    h.Load(arr.at(i).toObject());
    hills.push_back(h);
  }
  return hills;
}

void GuiJsonFile::Open(PlotArea& plot_area) {
  if (file_->open(QIODevice::ReadOnly | QFile::Text)) {
    json_file_ = new QJsonDocument(
        QJsonDocument::fromJson(QByteArray(file_->readAll())));

    QJsonObject root = json_file_->object();

    QJsonValue json_targets = root.value("Targets");
    QJsonValue json_trappy_circles = root.value("Trappy_Circles");
    QJsonValue json_trappy_lines = root.value("Trappy_Lines");
    QJsonValue json_hills = root.value("Hills");

    plot_area.Set(GetTargetsFromFile(json_targets.toArray(), plot_area));
    plot_area.Set(
        GetTrappyCirclesFromFile(json_trappy_circles.toArray(), plot_area));
    plot_area.Set(
        GetTrappyLinesFromFile(json_trappy_lines.toArray(), plot_area));
    plot_area.Set(GetHillsFromFile(json_hills.toArray(), plot_area));

    plot_area.Redraw();
    file_->close();
  }
}
