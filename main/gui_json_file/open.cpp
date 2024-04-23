#include "gui_json_file.h"

std::vector<lib::Target> GetTargetsFromFile(QJsonArray arr,
                                            data_tools::DataManager* manager) {
  std::vector<lib::Target> targets;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Target t;
    t.SetJsonInfo(arr.at(i).toObject());
    targets.push_back(t);
  }

  return targets;
}

std::vector<lib::TrappyCircle> GetTrappyCirclesFromFile(
    QJsonArray arr, data_tools::DataManager* manager) {
  std::vector<lib::TrappyCircle> trappy_circles;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyCircle tc;
    tc.SetJsonInfo(arr.at(i).toObject());
    trappy_circles.push_back(tc);
  }

  return trappy_circles;
}

std::vector<lib::TrappyLine> GetTrappyLinesFromFile(
    QJsonArray arr, data_tools::DataManager* manager) {
  std::vector<lib::TrappyLine> trappy_lines;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::TrappyLine tl;
    tl.SetJsonInfo(arr.at(i).toObject());
    trappy_lines.push_back(tl);
  }

  return trappy_lines;
}

std::vector<lib::Hill> GetHillsFromFile(QJsonArray arr,
                                        data_tools::DataManager* manager) {
  std::vector<lib::Hill> hills;
  for (size_t i = 0; i < arr.size(); i++) {
    lib::Hill h;
    h.SetJsonInfo(arr.at(i).toObject());
    hills.push_back(h);
  }

  return hills;
}

void GuiJsonFile::Open(data_tools::DataManager* manager) {
  if (file_->open(QIODevice::ReadOnly | QFile::Text)) {
    QJsonObject root = LoadJson();

    if (!(root.contains("Targets") && root.contains("Trappy_Circles") &&
          root.contains("Trappy_Lines") && root.contains("Hills")))
      throw std::invalid_argument("");

    QJsonArray json_targets = root["Targets"].toArray();
    QJsonArray json_trappy_circles = root["Trappy_Circles"].toArray();
    QJsonArray json_trappy_lines = root["Trappy_Lines"].toArray();
    QJsonArray json_hills = root["Hills"].toArray();

    manager->Set(GetTargetsFromFile(json_targets, manager));
    manager->Set(GetTrappyCirclesFromFile(json_trappy_circles, manager));
    manager->Set(GetTrappyLinesFromFile(json_trappy_lines, manager));
    manager->Set(GetHillsFromFile(json_hills, manager));

    file_->close();

    // перерисовка произойдёт уже после
  }
}
