#pragma once

typedef void* json;

namespace LIB {

class JSONable {
 public:
  // JSONable(const json& j);

  virtual json Save() const = 0;
  virtual JSONable* Load(const json& j) = 0;
};

}  // namespace LIB