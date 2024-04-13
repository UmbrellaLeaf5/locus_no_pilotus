#include "data_manager.h"

#include <icecream.hpp>

namespace data_tools {

void DataManager::Draw(gui::ObjectType obj_type, size_t index,
                       QCustomPlot* plot) {
  switch (obj_type) {
    case gui::ObjectType::Targets: {
      targets_[index].SetGraphIndex(plot->plottableCount());
      targets_[index].Draw(plot);
      break;
    }

    case gui::ObjectType::Hills: {
      hills_[index].SetGraphIndex(plot->plottableCount());
      hills_[index].Draw(plot);
      break;
    }

    case gui::ObjectType::TrappyCircles: {
      tr_circles_[index].SetItemIndex(plot->itemCount());
      tr_circles_[index].Draw(plot);
      break;
    }

    case gui::ObjectType::TrappyLines: {
      tr_lines_[index].SetGraphIndex(plot->plottableCount());
      tr_lines_[index].Draw(plot);
      break;
    }
  }
}

void DataManager::Remove(gui::ObjectType obj_type, size_t index) {
  switch (obj_type) {
    case gui::ObjectType::Targets: {
      targets_.erase(targets_.begin() + index);
      break;
    }

    case gui::ObjectType::Hills: {
      hills_.erase(hills_.begin() + index);
      break;
    }

    case gui::ObjectType::TrappyCircles: {
      tr_circles_.erase(tr_circles_.begin() + index);
      break;
    }

    case gui::ObjectType::TrappyLines: {
      tr_lines_.erase(tr_lines_.begin() + index);
      break;
    }
  }
}

void DataManager::Clear() {
  while (targets_.size() > 0) Remove(gui::ObjectType::Targets, 0);

  while (tr_circles_.size() > 0) Remove(gui::ObjectType::TrappyCircles, 0);

  while (tr_lines_.size() > 0) Remove(gui::ObjectType::TrappyLines, 0);

  while (hills_.size() > 0) Remove(gui::ObjectType::Hills, 0);
}

QString DataManager::GetTexted(gui::ObjectType obj_type) {
  QString text;

  switch (obj_type) {
    case gui::ObjectType::Targets: {
      text += "Targets on plot: \n";
      for (size_t i = 0; i < targets_.size(); i++) {
        auto target = targets_[i];
        text += "• target n." + QString::number(i + 1) + ":\n";
        text += "   plot id: " + QString::number(target.GetPlottableIndex()) +
                ":\n";
        text += "   x: " + QString::number(target.GetPoint().x) + "\n";
        text += "   y: " + QString::number(target.GetPoint().y) + "\n";
      }
      break;
    }

    case gui::ObjectType::Hills: {
      text += "Hills on plot: \n";
      for (size_t i = 0; i < hills_.size(); i++) {
        auto hill = hills_[i];
        text += "• hill n." + QString::number(i + 1) + ":\n";
        text +=
            "   plot id: " + QString::number(hill.GetPlottableIndex()) + ":\n";
        for (size_t j = 0; j < hill.GetPoints().size(); j++) {
          auto point = hill.GetPoints()[j];
          text += "   point n." + QString::number(j + 1) + ":\n";
          text += "    x: " + QString::number(point.x) + "\n";
          text += "    y: " + QString::number(point.y) + "\n";
        }
      }
      break;
    }

    case gui::ObjectType::TrappyCircles: {
      text += "Trappy circles on plot: \n";
      for (size_t i = 0; i < tr_circles_.size(); i++) {
        auto tr_circle = tr_circles_[i];
        text += "• trappy c. n." + QString::number(i + 1) + ":\n";
        text +=
            "   plot id: " + QString::number(tr_circle.GetItemIndex()) + ":\n";
        text += "   x: " + QString::number(tr_circle.GetCenter().x) + "\n";
        text += "   y: " + QString::number(tr_circle.GetCenter().y) + "\n";
        text += "   r: " + QString::number(tr_circle.GetRadius()) + "\n";
      }
      break;
    }

    case gui::ObjectType::TrappyLines: {
      text += "Trappy lines on plot: \n";
      for (size_t i = 0; i < tr_lines_.size(); i++) {
        auto tr_line = tr_lines_[i];
        text += "• trappy l. n." + QString::number(i + 1) + ":\n";
        text += "   plot id: " + QString::number(tr_line.GetPlottableIndex()) +
                ":\n";
        for (size_t j = 0; j < tr_line.GetTargets().size(); j++) {
          auto target = tr_line.GetTargets()[j];
          text += "   target n." + QString::number(j + 1) + ":\n";
          text += "    x: " + QString::number(target.GetPoint().x) + "\n";
          text += "    y: " + QString::number(target.GetPoint().y) + "\n";
        }
      }
      break;
    }
  }

  return text;
}

// ----------------------   Target methods   ----------------------

void DataManager::Add(std::initializer_list<gui::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Add(std::initializer_list<lib::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Add(std::vector<gui::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Add(std::vector<lib::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Set(std::initializer_list<gui::Target> targets) {
  targets_ = {targets.begin(), targets.end()};
}

void DataManager::Set(std::initializer_list<lib::Target> targets) {
  targets_ = {targets.begin(), targets.end()};
}

void DataManager::Set(std::vector<gui::Target> targets) { targets_ = targets; }

void DataManager::Set(std::vector<lib::Target> targets) {
  targets_.clear();
  for (const auto& target : targets) targets_.push_back(gui::Target(target));
}

// ----------------------    Hill methods    ----------------------

void DataManager::Add(std::initializer_list<gui::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Add(std::initializer_list<lib::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Add(std::vector<gui::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Add(std::vector<lib::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Set(std::initializer_list<gui::Hill> hills) {
  hills_ = {hills.begin(), hills.end()};
}

void DataManager::Set(std::initializer_list<lib::Hill> hills) {
  hills_ = {hills.begin(), hills.end()};
}

void DataManager::Set(std::vector<gui::Hill> hills) { hills_ = hills; }

void DataManager::Set(std::vector<lib::Hill> hills) {
  hills_.clear();
  for (const auto& hill : hills) hills_.push_back(gui::Hill(hill));
}

// ---------------------- TrappyCircle methods ----------------------s

void DataManager::Add(std::initializer_list<gui::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Add(std::initializer_list<lib::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Add(std::vector<gui::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Add(std::vector<lib::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Set(std::initializer_list<gui::TrappyCircle> tr_circles) {
  tr_circles_ = {tr_circles.begin(), tr_circles.end()};
}

void DataManager::Set(std::initializer_list<lib::TrappyCircle> tr_circles) {
  tr_circles_ = {tr_circles.begin(), tr_circles.end()};
}

void DataManager::Set(std::vector<gui::TrappyCircle> tr_circles) {
  tr_circles_ = tr_circles;
}

void DataManager::Set(std::vector<lib::TrappyCircle> tr_circles) {
  tr_circles_.clear();
  for (const auto& tr_circle : tr_circles)
    tr_circles_.push_back(gui::TrappyCircle(tr_circle));
}

// ----------------------  TrappyLine methods  ----------------------

void DataManager::Add(std::initializer_list<gui::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Add(std::initializer_list<lib::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Add(std::vector<gui::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Add(std::vector<lib::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Set(std::initializer_list<gui::TrappyLine> tr_lines) {
  tr_lines_ = {tr_lines.begin(), tr_lines.end()};
}

void DataManager::Set(std::initializer_list<lib::TrappyLine> tr_lines) {
  tr_lines_ = {tr_lines.begin(), tr_lines.end()};
}

void DataManager::Set(std::vector<gui::TrappyLine> tr_lines) {
  tr_lines_ = tr_lines;
}

void DataManager::Set(std::vector<lib::TrappyLine> tr_lines) {
  tr_lines_.clear();
  for (const auto& tr_line : tr_lines)
    tr_lines_.push_back(gui::TrappyLine(tr_line));
}

}  // namespace data_tools
