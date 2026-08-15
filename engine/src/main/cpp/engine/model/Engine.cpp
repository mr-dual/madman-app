#include "Engine.hpp"
#include "engine/context/EngineContext.hpp"
#include "engine/vulkan/VulkanContext.hpp"
#include "platforms/NativeWindow.hpp"
#include "util/Log.hpp"
#include <vulkan/vulkan.h>

//====================================================================
//  Engine State Controls
//====================================================================
Engine::Engine(EngineContext &context)
    : context(context), mGraphicsContext(std::make_unique<VulkanContext>()) {}

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

void Engine::resize(int w, int h) {
  height = h;
  width = w;

  mGraphicsContext->resize(w, h);
  LOGD("resized from cpp with dimentions %dx%d", height.load(), width.load());

  return;
}

//====================================================================
//  Engine Render Loop and Set Window
//====================================================================

void Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (isRunning) {
    mGraphicsContext->render();

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");
}

void Engine::setWindow(NativeWindow win) {
  window = win;
  mGraphicsContext->setWindow(win);
}
