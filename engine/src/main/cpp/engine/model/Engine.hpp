#pragma once

#include "context/EngineContext.hpp"
#include "context/GraphicsContext.hpp"
#include "platforms/NativeWindow.hpp"
#include <atomic>
#include <thread>

class Engine {
protected:
  NativeWindow window = nullptr;

private:
  std::thread _renderThread;
  std::atomic<bool> _isRunning{false};
  std::atomic<int> _height{0};
  std::atomic<int> _width{0};

  std::unique_ptr<GraphicsContext> _graphicsContext;
  EngineContext &_context;

  void renderLoop();

public:
  Engine(EngineContext &context);
  ~Engine();

  void setWindow(NativeWindow win);
  void start();
  void stopPhysics();
  void stopRender();
  void resize(int h, int w);
};
