#include "gui_json_file.h"

std::vector<lib::Target> GetTargetsFromFile(QJsonArray arr) {
  std::vector<lib::Target> targets;
  for (size_t i = 0; i < static_cast<size_t>(arr.size()); i++) {
    lib::Target t;
    t.SetJsonInfo(arr.at(i).toObject());
    targets.push_back(t);
  }
  return targets;
}

std::vector<lib::TrappyCircle> GetTrappyCirclesFromFile(QJsonArray arr) {
  std::vector<lib::TrappyCircle> trappy_circles;
  for (size_t i = 0; i < static_cast<size_t>(arr.size()); i++) {
    lib::TrappyCircle tc;
    tc.SetJsonInfo(arr.at(i).toObject());
    trappy_circles.push_back(tc);
  }
  return trappy_circles;
}

std::vector<lib::Hill> GetHillsFromFile(QJsonArray arr) {
  std::vector<lib::Hill> hills;
  for (size_t i = 0; i < static_cast<size_t>(arr.size()); i++) {
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
      throw std::invalid_argument(
          "Invalid file format: missing some objects fields!");

    QJsonArray json_targets = root["Targets"].toArray();
    QJsonArray json_trappy_circles = root["Trappy_Circles"].toArray();
    QJsonArray json_trappy_lines = root["Trappy_Lines"].toArray();
    QJsonArray json_hills = root["Hills"].toArray();

    std::vector<lib::Target> targets;

    for (size_t i = 0; i < static_cast<size_t>(json_targets.size()); i++) {
      lib::Target t;
      t.SetJsonInfo(json_targets.at(i).toObject());
      targets.push_back(t);
    }
    manager->Set(GetTargetsFromFile(json_targets));

    for (size_t i = 0; i < static_cast<size_t>(json_trappy_circles.size());
         i++) {
      lib::TrappyCircle trc;
      trc.SetJsonInfo(json_trappy_circles.at(i).toObject());
    }
    manager->Set(GetTrappyCirclesFromFile(json_trappy_circles));

    for (size_t i = 0; i < static_cast<size_t>(json_trappy_lines.size()); i++) {
      QJsonObject json_tr_line = json_trappy_lines.at(i).toObject();
      unsigned short id1 =
          static_cast<unsigned short>(json_tr_line.value("Id_P1").toInt());
      unsigned short id2 =
          static_cast<unsigned short>(json_tr_line.value("Id_P2").toInt());
      std::pair<gui::Target*, gui::Target*> targets_ptrs;
      for (const auto& target : manager->GetTargetsPtrs()) {
        if (target->GetData().GetId() == id1) targets_ptrs.first = target;
        if (target->GetData().GetId() == id2) targets_ptrs.second = target;
      }
      manager->Add(
          new gui::TrappyLine(targets_ptrs.first, targets_ptrs.second));
    }

    for (size_t i = 0; i < static_cast<size_t>(json_hills.size()); i++) {
      lib::Hill h;
      h.SetJsonInfo(json_hills.at(i).toObject());
    }
    manager->Set(GetHillsFromFile(json_hills));

    file_->close();
    // перерисовка произойдёт уже после
  }
}
