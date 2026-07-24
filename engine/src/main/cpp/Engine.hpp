#pragma once

#include <android/native_window.h>
#include <atomic>
#include <thread>

class Engine {
public:
  void setWindow(ANativeWindow *win);
  void start();
  void stop();
  void resize(int h, int w);

private:
  ANativeWindow *window = nullptr;
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  void renderLoop();
};
