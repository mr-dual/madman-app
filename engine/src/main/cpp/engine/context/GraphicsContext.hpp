#pragma once

#include "platforms/NativeWindow.hpp"

class GraphicsContext {
public:
  virtual ~GraphicsContext() = default;

  virtual void setWindow(const NativeWindow &win) = 0;
  virtual void init() = 0;
  virtual void render() = 0;
  virtual void cleanup() = 0;
  virtual void resize(int w, int h) = 0;
};
