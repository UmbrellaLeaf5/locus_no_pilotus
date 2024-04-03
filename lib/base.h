#pragma once

#include <QJsonDocument>
#include <QJsonObject>

using json = QJsonDocument;

namespace lib {

// @brief объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  // JSONable(const json& j);

  virtual QJsonObject Save(int id) const = 0;
  virtual JSONable* Load(const json& j) = 0;
};

}  // namespace lib
