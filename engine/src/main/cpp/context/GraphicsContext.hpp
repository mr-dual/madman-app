#pragma once

#include "platforms/NativeWindow.hpp"
#include <functional>
#include <vector>

class GraphicsContext {
public:
  virtual ~GraphicsContext() = default;

  std::function<std::vector<char>(const char *)> readFile;
  virtual void setWindow(const NativeWindow &win) = 0;
  virtual void init() = 0;
  virtual void render() = 0;
  virtual void cleanup() = 0;
  virtual void resize(int w, int h) = 0;
};
