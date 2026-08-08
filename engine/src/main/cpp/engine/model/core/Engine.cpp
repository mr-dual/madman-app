#include "Engine.hpp"
#include "engine/vulkan/VulkanContext.hpp"
#include "util/Log.hpp"
#include <vulkan/vulkan.h>

//====================================================================
//  Engine State Controls
//====================================================================
Engine::Engine() : mGraphicsContext(std::make_unique<VulkanContext>()) {}

Engine::~Engine() { mGraphicsContext->cleanup(); }

void Engine::start() {
  if (isRunning)
    return;

  mGraphicsContext->init();

  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);

  return;
}

void Engine::stopRender() {
  if (!isRunning)
    return;

  isRunning = false;

  if (renderThread.joinable()) {
    renderThread.join();
  }

  mGraphicsContext->cleanup();
  return;
}

void Engine::resize(int h, int w) {
  height = h;
  width = w;

  mGraphicsContext->resize(h, w);
  LOGD("resized from cpp with dimentions %dx%d", height.load(), width.load());

  return;
}

//====================================================================
//  Engine Render Loop and Set Window
//====================================================================

void Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (isRunning) {
    if (window != nullptr) {
      mGraphicsContext->render();
    } else {
      LOGE("window is null");
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");
}

void Engine::setWindow(ANativeWindow *win) { window = win; }
