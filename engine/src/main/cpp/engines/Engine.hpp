#pragma once

#include <android/native_window.h>
#include <atomic>
#include <thread>
#include <vulkan/vulkan_core.h>

#ifdef NDEBUG
constexpr bool isDebug = false;
#else
constexpr bool isDebug = true;
#endif

#ifndef APPLICATION_NAME
#define APPLICATION_NAME "Madman"
#endif

#ifndef APP_VERSION_MAJOR
#define APP_VERSION_MAJOR 0
#endif

#ifndef APP_VERSION_MINOR
#define APP_VERSION_MINOR 1
#endif

#ifndef APP_VERSION_PATCH
#define APP_VERSION_PATCH 0
#endif

#ifndef APPLICATION_VERSION
#define APPLICATION_VERSION                                                    \
  VK_MAKE_VERSION(APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH)
#endif

class Engine {
protected:
  ANativeWindow *window;

private:
  VkInstance instance = nullptr;
  VkDebugUtilsMessengerEXT debugMessenger = nullptr;
  VkPhysicalDevice physicalDevice = nullptr;

  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  static std::vector<char const *> getRequiredLayers();
  static std::vector<char const *> getRequiredExtensions();

  void initVulkan();
  void cleanupVulkan();
  void createInstance();
  void setPhysicalDevice();
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
  Engine(ANativeWindow *win) : window(win) {};
  //~Engine();

  void start();
  void stop();
  void resize(int h, int w);
};
