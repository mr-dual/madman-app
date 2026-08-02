#pragma once

#include <android/native_window.h>
#include <atomic>
#include <thread>
// #include <vulkan/vulkan.h>

#ifdef NDEBUG
constexpr bool isDebug = false;
#else
constexpr bool isDebug = true;
#endif

class Engine {
protected:
  ANativeWindow *window;

private:
  // vk::raii::Context context;
  // vk::raii::Instance instance = nullptr;
  // vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;
  // vk::raii::PhysicalDevice physicalDevice = nullptr;

  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  std::vector<char const *> getRequiredLayers();
  std::vector<char const *> getRequiredExtensions();

  void initVulkan();
  void setInstance();
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

class Engine2d : public Engine {
public:
  Engine2d(ANativeWindow *win) : Engine(win) {};
};

class Engine3d : public Engine {
public:
  Engine3d(ANativeWindow *win) : Engine(win) {};
};
