#include "data_manager.h"

#include <icecream.hpp>

namespace data_tools {

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
  targets_.clear();
  tr_circles_.clear();
  tr_lines_.clear();
  hills_.clear();
}

// ----------------------   Target methods   ----------------------

void DataManager::Add(std::initializer_list<gui::Target*> new_targets) {
  for (const auto& target : new_targets) Add(target);
}

void DataManager::Add(std::initializer_list<lib::Target> new_targets) {
  for (const auto& target : new_targets) Add(target);
}

void DataManager::Add(std::vector<gui::Target*> new_targets) {
  for (const auto& target : new_targets) Add(target);
}

void DataManager::Add(std::vector<lib::Target> new_targets) {
  for (const auto& target : new_targets) Add(target);
}

void DataManager::Set(std::initializer_list<gui::Target*> targets) {
  targets_.clear();
  for (const auto& target : targets) Add(target);
}

void DataManager::Set(std::initializer_list<lib::Target> targets) {
  targets_.clear();
  for (const auto& target : targets) Add(target);
}

void DataManager::Set(std::vector<gui::Target*> targets) {
  targets_.clear();
  for (const auto& target : targets) Add(target);
}

void DataManager::Set(std::vector<lib::Target> targets) {
  targets_.clear();
  for (const auto& target : targets) Add(target);
}

std::vector<gui::Target*> DataManager::GetTargetsPtrs() {
  auto res = std::vector<gui::Target*>();
  for (auto& target_ptr_ : targets_) {
    res.push_back(target_ptr_.get());
  }

  return res;
}

std::vector<gui::Target> DataManager::GetTargets() const {
  auto res = std::vector<gui::Target>();
  for (auto& target_ptr_ : targets_) {
    res.push_back(*target_ptr_);
  }

  return res;
}

// ----------------------    Hill methods    ----------------------

void DataManager::Add(std::initializer_list<gui::Hill*> new_hills) {
  for (const auto& hill : new_hills) Add(hill);
}

void DataManager::Add(std::initializer_list<lib::Hill> new_hills) {
  for (const auto& hill : new_hills) Add(hill);
}

void DataManager::Add(std::vector<gui::Hill*> new_hills) {
  for (const auto& hill : new_hills) Add(hill);
}

void DataManager::Add(std::vector<lib::Hill> new_hills) {
  for (const auto& hill : new_hills) Add(hill);
}

void DataManager::Set(std::initializer_list<gui::Hill*> hills) {
  hills_.clear();
  for (const auto& hill : hills) Add(hill);
}

void DataManager::Set(std::initializer_list<lib::Hill> hills) {
  hills_.clear();
  for (const auto& hill : hills) Add(hill);
}

void DataManager::Set(std::vector<gui::Hill*> hills) {
  hills_.clear();
  for (const auto& hill : hills) Add(hill);
}

void DataManager::Set(std::vector<lib::Hill> hills) {
  hills_.clear();
  for (const auto& hill : hills) Add(hill);
}

std::vector<gui::Hill*> DataManager::GetHillsPtrs() {
  auto res = std::vector<gui::Hill*>();
  for (auto& hill_ptr_ : hills_) {
    res.push_back(hill_ptr_.get());
  }

  return res;
}

std::vector<gui::Hill> DataManager::GetHills() const {
  auto res = std::vector<gui::Hill>();
  for (auto& hill_ptr_ : hills_) {
    res.push_back(*hill_ptr_);
  }

  return res;
}

// ---------------------- TrappyCircle methods ----------------------s

void DataManager::Add(
    std::initializer_list<gui::TrappyCircle*> new_tr_circles) {
  for (const auto& tr_circle : new_tr_circles) Add(tr_circle);
}

void DataManager::Add(std::initializer_list<lib::TrappyCircle> new_tr_circles) {
  for (const auto& tr_circle : new_tr_circles) Add(tr_circle);
}

void DataManager::Add(std::vector<gui::TrappyCircle*> new_tr_circles) {
  for (const auto& tr_circle : new_tr_circles) Add(tr_circle);
}

void DataManager::Add(std::vector<lib::TrappyCircle> new_tr_circles) {
  for (const auto& tr_circle : new_tr_circles) Add(tr_circle);
}

void DataManager::Set(std::initializer_list<gui::TrappyCircle*> tr_circles) {
  tr_circles_.clear();
  for (const auto& tr_circle : tr_circles) Add(tr_circle);
}

void DataManager::Set(std::initializer_list<lib::TrappyCircle> tr_circles) {
  tr_circles_.clear();
  for (const auto& tr_circle : tr_circles) Add(tr_circle);
}

void DataManager::Set(std::vector<gui::TrappyCircle*> tr_circles) {
  tr_circles_.clear();
  for (const auto& tr_circle : tr_circles) Add(tr_circle);
}

void DataManager::Set(std::vector<lib::TrappyCircle> tr_circles) {
  tr_circles_.clear();
  for (const auto& tr_circle : tr_circles) Add(tr_circle);
}

std::vector<gui::TrappyCircle*> DataManager::GetTrappyCirclesPtrs() {
  auto res = std::vector<gui::TrappyCircle*>();
  for (auto& tr_circle_ptr : tr_circles_) {
    res.push_back(tr_circle_ptr.get());
  }

  return res;
}

std::vector<gui::TrappyCircle> DataManager::GetTrappyCircles() const {
  auto res = std::vector<gui::TrappyCircle>();
  for (auto& tr_circle_ptr : tr_circles_) {
    res.push_back(*tr_circle_ptr);
  }

  return res;
}

// ----------------------  TrappyLine methods  ----------------------

void DataManager::Add(std::initializer_list<gui::TrappyLine*> new_tr_lines) {
  for (const auto& tr_line : new_tr_lines) Add(tr_line);
}

void DataManager::Add(std::initializer_list<lib::TrappyLine> new_tr_lines) {
  for (const auto& tr_line : new_tr_lines) Add(tr_line);
}

void DataManager::Add(std::vector<gui::TrappyLine*> new_tr_lines) {
  for (const auto& tr_line : new_tr_lines) Add(tr_line);
}

void DataManager::Add(std::vector<lib::TrappyLine> new_tr_lines) {
  for (const auto& tr_line : new_tr_lines) Add(tr_line);
}

void DataManager::Set(std::initializer_list<gui::TrappyLine*> tr_lines) {
  tr_lines_.clear();
  for (const auto& tr_line : tr_lines) Add(tr_line);
}

void DataManager::Set(std::initializer_list<lib::TrappyLine> tr_lines) {
  tr_lines_.clear();
  for (const auto& tr_line : tr_lines) Add(tr_line);
}

void DataManager::Set(std::vector<gui::TrappyLine*> tr_lines) {
  tr_lines_.clear();
  for (const auto& tr_line : tr_lines) Add(tr_line);
}

void DataManager::Set(std::vector<lib::TrappyLine> tr_lines) {
  tr_lines_.clear();
  for (const auto& tr_line : tr_lines) Add(tr_line);
}

std::vector<gui::TrappyLine*> DataManager::GetTrappyLinesPtrs() {
  auto res = std::vector<gui::TrappyLine*>();
  for (auto& tr_line_ptr : tr_lines_) {
    res.push_back(tr_line_ptr.get());
  }

  return res;
}

std::vector<gui::TrappyLine> DataManager::GetTrappyLines() const {
  auto res = std::vector<gui::TrappyLine>();
  for (auto& tr_line_ptr : tr_lines_) {
    res.push_back(*tr_line_ptr);
  }

  return res;
}

}  // namespace data_tools
