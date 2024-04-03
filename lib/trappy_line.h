#pragma once

#include <initializer_list>
#include <vector>

#include "base.h"
#include "target.h"

namespace lib {

// @brief линия опасного перелета
class TrappyLine : public JSONable {
 public:
  TrappyLine() = default;

  /**
   * @brief инициализирует новый экземпляр Trappy Line
   * (конструктор исключительно по КТ, только между ними может быть перелет)
   * @param targets: лист контрольных точек
   */
  TrappyLine(std::initializer_list<Target> targets) : targets_{targets} {}

  /**
   * @brief инициализирует новый экземпляр Trappy Line
   * (конструктор исключительно по КТ, только между ними может быть перелет)
   * @param targets: вектор контрольных точек
   */
  TrappyLine(std::vector<Target> targets) : targets_{targets} {}

  TrappyLine(const TrappyLine&) = default;
  TrappyLine(TrappyLine&&) = default;

  TrappyLine& operator=(const TrappyLine&) = default;
  TrappyLine& operator=(TrappyLine&&) = default;

  QJsonObject Save(int id) const override;
  JSONable* Load(const json& j) override;

  void SetNewTargets(std::initializer_list<Target> targets) {
    targets_ = targets;
  }

  void SetNewTargets(std::vector<Target> targets) { targets_ = targets; }

  void AddTargets(std::initializer_list<Target> targets);
  void AddTargets(std::vector<Target> targets);

  std::vector<Target> GetTargets() const { return targets_; }

 private:
  std::vector<Target> targets_;
};

}  // namespace lib
