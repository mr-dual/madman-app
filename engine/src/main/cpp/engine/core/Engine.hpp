#pragma once

#include "engine/graphicsContext/GraphicsContext.hpp"
#include <android/native_window.h>
#include <atomic>
#include <memory>
#include <thread>
#include <vulkan/vulkan_core.h>

class Engine {
protected:
  ANativeWindow *window;

private:
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::unique_ptr<GraphicsContext> mGraphicsContext;

  // bool isDeviceSupported(const vk::raii::PhysicalDevice &physicalDevice);

  void renderLoop();

  // Debug Mode Stuff
  // void setDebugMessenger();
  // static VKAPI_ATTR VkBool32 VKAPI_CALL
  // debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  //               VkDebugUtilsMessageTypeFlagsEXT messageType,
  //               const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
  //               void *pUserData);

public:
  Engine(ANativeWindow *win);
  ~Engine();

  void start();
  void stop();
  void resize(int h, int w);
};
