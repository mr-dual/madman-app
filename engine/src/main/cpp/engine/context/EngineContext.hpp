#pragma once

#include <chrono>

class EngineContext {
public:
  double physHz;
  std::chrono::duration<double> fixedDelta;

  explicit EngineContext(const double physHz = 240.0)
      : physHz(physHz), fixedDelta(1.0 / physHz) {}
};
