#pragma once

#include "engine/context/EngineContext.hpp"
#include "engine/context/GraphicsContext.hpp"
#include "platforms/NativeWindow.hpp"
#include <atomic>
#include <thread>

class Engine {
protected:
  NativeWindow window = nullptr;

private:
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::unique_ptr<GraphicsContext> mGraphicsContext;
  EngineContext &context;

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
