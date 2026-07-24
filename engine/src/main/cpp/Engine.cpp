#include "Engine.hpp"
#include <android/log.h>

#define LOG_TAG "MadmanEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void Engine::setWindow(ANativeWindow *win) { window = win; }

void Engine::start() {
  if (isRunning)
    return;
  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);
}

void Engine::stop() {
  if (!isRunning)
    return;
  isRunning = false;
  if (renderThread.joinable()) {
    renderThread.join();
  }
  if (window) {
    ANativeWindow_release(window);
    window = nullptr;
  }
}

void Engine::resize(int h, int w) {
  height = h;
  width = w;

  LOGI("resized from cpp with dimentions %dx%d", height.load(), width.load());
}

void Engine::renderLoop() {
  LOGI("Render started in cpp.");

  while (isRunning) {
    if (window != nullptr) {
      LOGI("window isnt null");
    } else {
      LOGI("window is null");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGI("Render stopped in cpp.");
}
