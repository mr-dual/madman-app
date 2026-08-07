#pragma once

#include <chrono>

class EngineConfigs {
public:
  const double physHz = 240.0;
  std::chrono::duration<double> fixedDelta;

  EngineConfigs(const double physHz)
      : physHz(physHz), fixedDelta(1.0 / physHz) {}
};
