#pragma once

#include <QJsonArray>
#include <QJsonObject>

namespace lib {

/// @brief Объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  virtual QJsonObject Load(int id) const = 0;
  virtual void Save(const QJsonObject& obj) = 0;
  virtual bool IsChanged(const QJsonObject& obj) const = 0;
};

}  // namespace lib
