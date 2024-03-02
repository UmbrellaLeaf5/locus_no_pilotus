#pragma once

typedef void* json;

namespace LIB {

class JSONable {
 public:
  // JSONable(const json& j);

  virtual json save() const = 0;
  virtual JSONable load(const json& j) = 0;
};

}  // namespace LIB