#pragma once

#include <QJsonObject>

namespace lib {

// @brief объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  virtual QJsonObject Save(int id) const = 0;
  virtual void Load(QJsonObject obj) = 0;
  virtual bool IsChanged(QJsonObject obj) = 0;
};

}  // namespace lib
