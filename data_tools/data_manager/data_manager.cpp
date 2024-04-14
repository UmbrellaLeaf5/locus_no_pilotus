#include "data_manager.h"

#include <icecream.hpp>

namespace data_tools {

void DataManager::Clear() {
  targets_.clear();
  tr_circles_.clear();
  tr_lines_.clear();
  hills_.clear();
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
