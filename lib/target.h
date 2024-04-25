#pragma once

#include "base.h"
#include "point.h"

namespace lib {

/// @brief Контрольная точка
class Target : public JSONable {
 public:
  Target(double x, double y) : p_(x, y) { CheckErrorValues(); }
  Target(const Point& p) : p_{p} { CheckErrorValues(); }
  Target() : p_(0, 0) {}

  Target(const Target&) = default;
  Target(Target&&) = default;

  Target& operator=(const Target&) = default;
  Target& operator=(Target&&) = default;

  QJsonObject GetJsonInfo(int id) const override;
  void SetJsonInfo(const QJsonObject& target_obj) override;
  bool IsChanged(const QJsonObject& target_obj) const override;

  Point GetPoint() const { return p_; }

  void SetPoint(const Point& p) {
    p_ = p;
    CheckErrorValues();
  }

  void SetPoint(double x, double y) {
    p_ = Point(x, y);
    CheckErrorValues();
  }

  bool operator==(const Target&) const;

 private:
  /**
   * @brief Проверяет данные в классе на валидность
   * @throw std::invalid_argument: если одна из коорд. точки превышает
   * максимально допустимое значение
   */
  void CheckErrorValues() const override;

  Point p_;
};

}  // namespace lib
