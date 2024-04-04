#include "data_manager.h"

#include "icecream.hpp"

namespace gui {

void DataManager::Draw(ObjectType obj_type, size_t index, QCustomPlot* plot) {
  switch (obj_type) {
    case ObjectType::Targets: {
      targets_[index].SetGraphIndex(plot->plottableCount());
      targets_[index].Draw(plot);
      break;
    }

    case ObjectType::Hills: {
      hills_[index].SetGraphIndex(plot->plottableCount());
      hills_[index].Draw(plot);
      break;
    }

    case ObjectType::TrappyCircles: {
      tr_circles_[index].SetItemIndex(plot->itemCount());
      tr_circles_[index].Draw(plot);
      break;
    }

    case ObjectType::TrappyLines: {
      tr_lines_[index].SetGraphIndex(plot->plottableCount());
      tr_lines_[index].Draw(plot);
      break;
    }
  }
}

// ----------------------   Target methods   ----------------------

QString DataManager::GetTexted(ObjectType obj_type) {
  QString text;

  switch (obj_type) {
    case ObjectType::Targets: {
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

    case ObjectType::Hills: {
      text += "Hills on plot: \n";
      for (size_t i = 0; i < hills_.size(); i++) {
        auto hill = hills_[i];
        text += "• hill n." + QString::number(i + 1) + ":\n";
        text +=
            "   plot id: " + QString::number(hill.GetPlottableIndex()) + ":\n";
        text += "   x: " + QString::number(hill.GetCenter().x) + "\n";
        text += "   y: " + QString::number(hill.GetCenter().y) + "\n";
        text += "   r: " + QString::number(hill.GetRadius()) + "\n";
      }
      break;
    }

    case ObjectType::TrappyCircles: {
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

    case ObjectType::TrappyLines: {
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

void DataManager::Add(std::initializer_list<gui::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Add(std::vector<gui::Target> new_targets) {
  targets_.insert(targets_.end(), new_targets.begin(), new_targets.end());
}

void DataManager::Set(std::initializer_list<gui::Target> targets) {
  targets_ = {targets.begin(), targets.end()};
}

void DataManager::Set(std::vector<gui::Target> targets) { targets_ = targets; }

// ----------------------    Hill methods    ----------------------

void DataManager::Add(std::initializer_list<gui::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Add(std::vector<gui::Hill> new_hills) {
  hills_.insert(hills_.end(), new_hills.begin(), new_hills.end());
}

void DataManager::Set(std::initializer_list<gui::Hill> hills) {
  hills_ = {hills.begin(), hills.end()};
}

void DataManager::Set(std::vector<gui::Hill> hills) { hills_ = hills; }

// ---------------------- TrappyCircle methods ----------------------s

void DataManager::Add(std::initializer_list<gui::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Add(std::vector<gui::TrappyCircle> new_tr_circles) {
  tr_circles_.insert(tr_circles_.end(), new_tr_circles.begin(),
                     new_tr_circles.end());
}

void DataManager::Set(std::initializer_list<gui::TrappyCircle> tr_circles) {
  tr_circles_ = {tr_circles.begin(), tr_circles.end()};
}

void DataManager::Set(std::vector<gui::TrappyCircle> tr_circles) {
  tr_circles_ = tr_circles;
}

// ----------------------  TrappyLine methods  ----------------------

void DataManager::Add(std::initializer_list<gui::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Add(std::vector<gui::TrappyLine> new_tr_lines) {
  tr_lines_.insert(tr_lines_.end(), new_tr_lines.begin(), new_tr_lines.end());
}

void DataManager::Set(std::initializer_list<gui::TrappyLine> tr_lines) {
  tr_lines_ = {tr_lines.begin(), tr_lines.end()};
}

void DataManager::Set(std::vector<gui::TrappyLine> tr_lines) {
  tr_lines_ = tr_lines;
}

}  // namespace gui