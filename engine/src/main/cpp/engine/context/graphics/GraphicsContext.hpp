#pragma once

class GraphicsContext {
public:
  virtual ~GraphicsContext() = default;

  virtual void init() = 0;
  virtual void render() = 0;
  virtual void cleanup() = 0;
  virtual void resize(int h, int w) = 0;
};
