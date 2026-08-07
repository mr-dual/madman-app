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
  Engine(ANativeWindow *win);
  ~Engine();

  void start();
  void stop();
  void resize(int h, int w);
};
