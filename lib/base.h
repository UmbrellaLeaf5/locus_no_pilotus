#pragma once

using json = void*;

namespace lib {

// @brief объект, возможный к считыванию по .json файлу [абстрактный класс]
class JSONable {
 public:
  // JSONable(const json& j);

  virtual json Save() const = 0;
  virtual JSONable* Load(const json& j) = 0;
};

}  // namespace lib
