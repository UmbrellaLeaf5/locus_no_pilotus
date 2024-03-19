#pragma once

using json = void*;

namespace lib {

class JSONable {
 public:
  // JSONable(const json& j);

  virtual json Save() const = 0;
  virtual JSONable* Load(const json& j) = 0;
};

}  // namespace lib
