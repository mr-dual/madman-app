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
    : _context(context), _graphicsContext(std::make_unique<VulkanContext>()) {}

Engine::~Engine() { _graphicsContext->cleanup(); }

void Engine::start() {
  if (_isRunning)
    return;

  _graphicsContext->init();

  _isRunning = true;
  _renderThread = std::thread(&Engine::renderLoop, this);

  return;
}

void Engine::stopRender() {
  if (!_isRunning)
    return;

  _isRunning = false;

  if (_renderThread.joinable()) {
    _renderThread.join();
  }

  _graphicsContext->cleanup();
  return;
}

void Engine::resize(int w, int h) {
  _height = h;
  _width = w;

  _graphicsContext->resize(w, h);
  LOGD("resized from cpp with dimentions %dx%d", _height.load(), _width.load());

  return;
}

//====================================================================
//  Engine Render Loop and Set Window
//====================================================================

void Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (_isRunning) {
    _graphicsContext->render();

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");
}

void Engine::setWindow(NativeWindow win) {
  window = win;
  _graphicsContext->setWindow(win);
}
