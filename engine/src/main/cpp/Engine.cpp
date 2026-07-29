#include "Engine.hpp"
#include "util/Log.hpp"
#include <string>
#include <vector>

//====================================================================
// Lifecycle & Setup
//====================================================================

Engine &Engine::setWindow(ANativeWindow *win) {
  window = win;
  return *this;
}

Engine &Engine::initVulkan() {

  if (*instance != nullptr) {
    LOGD("Instance exists, skipping creation.");
    return *this;
  }

  try {
    setInstance();

    if constexpr (isDebug) {
      setDebugMessenger();
    }

  } catch (const vk::SystemError &err) {
    LOGE("Vulkan System Error: %s at line %d", err.what(), err.code().value());

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }

  return *this;
}

Engine &Engine::setInstance() {
  std::vector<char const *> requiredLayers = getRequiredLayers();
  std::vector<char const *> extensions = getRequiredExtensions();

  constexpr vk::ApplicationInfo appInfo(
      "Madman", VK_MAKE_VERSION(0, 1, 0), "MadmanEngine",
      VK_MAKE_VERSION(0, 1, 0), vk::ApiVersion10);

  vk::InstanceCreateInfo createInfo(
      {}, &appInfo, static_cast<uint32_t>(requiredLayers.size()),
      requiredLayers.data(), static_cast<uint32_t>(extensions.size()),
      extensions.data());

  instance = vk::raii::Instance(context, createInfo);

  LOGD("Instance created!");

  return *this;
};
//====================================================================
//  Get Extensions and Layers
//====================================================================

std::vector<char const *> Engine::getRequiredLayers() {
  if constexpr (isDebug) {

    const std::vector<char const *> validationLayers{
        "VK_LAYER_KHRONOS_validation"};
    auto layerProperties = context.enumerateInstanceLayerProperties();

    for (const auto &validationLayer : validationLayers) {
      bool found = false;

      for (const auto &layerProperty : layerProperties) {
        if (strcmp(validationLayer, layerProperty.layerName.data()) == 0) {
          found = true;
          break;
        }
      }

      if (!found) {
        LOGE("Validation Layer %s not found.", validationLayer);
        return {};
      }
    }
    return validationLayers;
  }
  return {};
}

std::vector<char const *> Engine::getRequiredExtensions() {

  std::vector<char const *> extensions = {"VK_KHR_surface",
                                          "VK_KHR_android_surface"};

  if constexpr (isDebug) {
    extensions.push_back(vk::EXTDebugUtilsExtensionName);
  }

  return extensions;
}

//====================================================================
//  Engine State Controls
//====================================================================

Engine &Engine::start() {
  if (isRunning)
    return *this;

  initVulkan();

  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);

  return *this;
}

Engine &Engine::stop() {
  if (!isRunning)
    return *this;

  isRunning = false;

  if (renderThread.joinable()) {
    renderThread.join();
  }

  if (window) {
    ANativeWindow_release(window);
    window = nullptr;
  }

  return *this;
}

Engine &Engine::resize(int h, int w) {
  height = h;
  width = w;

  LOGD("resized from cpp with dimentions %dx%d", height.load(), width.load());

  return *this;
}

//====================================================================
//  Engine Render Loop
//====================================================================

Engine &Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (isRunning) {
    if (window != nullptr) {
    } else {
      LOGI("window is null");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");

  return *this;
}

//====================================================================
//  Debug Functions
//====================================================================
Engine &Engine::setDebugMessenger() {

  vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);

  vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
      vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
      vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

  vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT(
      {}, severityFlags, messageTypeFlags, &debugCallback);

  debugMessenger =
      instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
  LOGD("Debug Messenger Initialized!");
  return *this;
}

VKAPI_ATTR VkBool32 VKAPI_CALL
Engine::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                      VkDebugUtilsMessageTypeFlagsEXT messageType,
                      const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                      void *pUserData) {

  auto cppType = static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(messageType);
  std::string typeStr = vk::to_string(cppType);

  auto cppSeverity =
      static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity);

  switch (cppSeverity) {
  case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
    LOGW("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
    break;

  case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
    LOGE("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
    break;

  default:
    LOGI("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
    break;
  }

  return VK_FALSE;
}
