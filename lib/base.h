#pragma once

#include <QJsonArray>
#include <QJsonObject>

namespace lib {

/// @brief Объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  virtual QJsonObject GetJsonInfo(int id) const = 0;
  virtual void SetJsonInfo(const QJsonObject& obj) = 0;
  virtual bool IsChanged(const QJsonObject& obj) const = 0;
};

}  // namespace lib
