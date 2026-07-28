#pragma once

#include <android/native_window.h>
#include <atomic>
#include <thread>
#include <vulkan/vulkan_raii.hpp>

class Engine {
private:
  vk::raii::Context context;
  vk::raii::Instance instance = nullptr;
  vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;

  ANativeWindow *window = nullptr;
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::vector<char const *> getRequiredLayers();
  std::vector<char const *> getRequiredExtensions();
  void renderLoop();

public:
  // Engine();
  //~Engine();

  void setWindow(ANativeWindow *win);
  void start();
  void stop();
  void resize(int h, int w);
  void initVulkan();
};
