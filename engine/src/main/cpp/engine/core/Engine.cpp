#include "Engine.hpp"
#include "engine/vulkan/VulkanContext.hpp"
#include "util/Log.hpp"
#include <vulkan/vulkan.h>

//====================================================================
//  Engine State Controls
//====================================================================
Engine::Engine(ANativeWindow *win)
    : window(win), mGraphicsContext(std::make_unique<VulkanContext>()) {}

Engine::~Engine() = default;

void Engine::start() {
  if (isRunning)
    return;

  mGraphicsContext->init();

  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);

  return;
}

void Engine::stop() {
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
//  Engine Render Loop and Cleanup
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
