#pragma once

#include <android/native_window.h>
#include <atomic>
#include <thread>
#include <vulkan/vulkan_raii.hpp>

#ifdef NDEBUG
constexpr bool isDebug = false;
#else
constexpr bool isDebug = true;
#endif

class Engine {
private:
  ANativeWindow *window = nullptr;

  vk::raii::Context context;
  vk::raii::Instance instance = nullptr;
  vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;

  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::vector<char const *> getRequiredLayers();
  std::vector<char const *> getRequiredExtensions();

  Engine &initVulkan();
  Engine &setInstance();

  Engine &renderLoop();

  // Debug Mode Stuff

  Engine &setDebugMessenger();
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);

public:
  // Engine();
  //~Engine();

  Engine &setWindow(ANativeWindow *win);
  Engine &start();
  Engine &stop();
  Engine &resize(int h, int w);
};
