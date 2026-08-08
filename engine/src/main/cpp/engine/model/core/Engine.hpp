#pragma once

#include "engine/context/graphics/GraphicsContext.hpp"
#include <android/native_window.h>
#include <atomic>
#include <thread>

class Engine {
protected:
  ANativeWindow *window;

private:
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::unique_ptr<GraphicsContext> mGraphicsContext;

  void renderLoop();

public:
  Engine();
  ~Engine();

  void setWindow(ANativeWindow *win);
  void start();
  void stopPhysics();
  void stopRender();
  void resize(int h, int w);
};
