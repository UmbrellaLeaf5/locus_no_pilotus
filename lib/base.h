#pragma once

#include <QJsonArray>
#include <QJsonObject>

// lib::Point is used everywhere with lib classes
#include "point.h"

namespace lib {

constexpr double max_coord = 1000000;

/// @brief Объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  virtual QJsonObject GetJsonInfo() const = 0;
  virtual void SetJsonInfo(const QJsonObject& obj) = 0;
  virtual bool IsChanged(const QJsonObject& obj) const = 0;
  virtual unsigned short GetId() const { return id_; }
  virtual void SetId(unsigned short id) { id_ = id; }

 protected:
  virtual void CheckErrorValues() const = 0;

 private:
  unsigned short id_{USHRT_MAX};
};

}  // namespace lib
