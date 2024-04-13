#include "gui_json_file.h"

std::vector<lib::Target> GetTargetsFromFile(QJsonArray arr,
                                            data_tools::PlotArea& plot_area) {
  std::vector<lib::Target> targets;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Target t;
    t.Load(arr.at(i).toObject());
    targets.push_back(t);
  }
  return targets;
}

std::vector<lib::TrappyCircle> GetTrappyCirclesFromFile(
    QJsonArray arr, data_tools::PlotArea& plot_area) {
  std::vector<lib::TrappyCircle> trappy_circles;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyCircle tc;
    tc.Load(arr.at(i).toObject());
    trappy_circles.push_back(tc);
  }
  return trappy_circles;
}

std::vector<lib::TrappyLine> GetTrappyLinesFromFile(
    QJsonArray arr, data_tools::PlotArea& plot_area) {
  std::vector<lib::TrappyLine> trappy_lines;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyLine tl;
    tl.Load(arr.at(i).toObject());
    trappy_lines.push_back(tl);
  }
  return trappy_lines;
}

std::vector<lib::Hill> GetHillsFromFile(QJsonArray arr,
                                        data_tools::PlotArea& plot_area) {
  std::vector<lib::Hill> hills;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Hill h;
    h.Load(arr.at(i).toObject());
    hills.push_back(h);
  }
  return hills;
}

void GuiJsonFile::Open(data_tools::PlotArea& plot_area) {
  if (file_->open(QIODevice::ReadOnly | QFile::Text)) {
    QJsonObject root = LoadJson();

    if (root.contains("Targets") + root.contains("Trappy_Circles") +
            root.contains("Trappy_Lines") + root.contains("Hills") !=
        4)
      throw std::invalid_argument("");

    QJsonArray json_targets = root["Targets"].toArray();
    QJsonArray json_trappy_circles = root["Trappy_Circles"].toArray();
    QJsonArray json_trappy_lines = root["Trappy_Lines"].toArray();
    QJsonArray json_hills = root["Hills"].toArray();

    plot_area.Set(GetTargetsFromFile(json_targets, plot_area));
    plot_area.Set(GetTrappyCirclesFromFile(json_trappy_circles, plot_area));
    plot_area.Set(GetTrappyLinesFromFile(json_trappy_lines, plot_area));
    plot_area.Set(GetHillsFromFile(json_hills, plot_area));

    plot_area.Redraw();
    file_->close();
  }
}
