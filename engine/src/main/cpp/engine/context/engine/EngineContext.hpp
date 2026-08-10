#pragma once

#include <chrono>

class EngineContext {
public:
  const double physHz = 240.0;
  std::chrono::duration<double> fixedDelta;

  EngineContext(const double physHz)
      : physHz(physHz), fixedDelta(1.0 / physHz) {}
};
