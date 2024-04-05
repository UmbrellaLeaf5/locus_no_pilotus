#pragma once

#include <QJsonDocument>
#include <QJsonObject>

namespace lib {

// @brief объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  // JSONable(const json& j);

  virtual QJsonObject Save(int id) const = 0;
  virtual void Load(QJsonObject obj) = 0;
};

}  // namespace lib
