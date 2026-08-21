#pragma once

#include <chrono>
#include <functional>
#include <vector>

class EngineContext {
public:
  double physHz;
  std::chrono::duration<double> fixedDelta;

  std::function<std::vector<char>(const char *)> readFile;

  explicit EngineContext(const double physHz = 240.0)
      : physHz(physHz), fixedDelta(1.0 / physHz) {}
};
