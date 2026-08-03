#include "Engine.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

//====================================================================
// Lifecycle & Setup
//====================================================================

void Engine::initVulkan() {
  // if (*instance != nullptr) {
  //   LOGD("Instance exists, skipping creation.");
  // }

  try {
    createInstance();
    // if constexpr (isDebug)
    //   setDebugMessenger();
    setPhysicalDevice();

    // } catch (const vk::SystemError &err) {
    //   LOGE("Vulkan System Error: %s at line %d", err.what(),
    //   err.code().value());
    //
  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

void Engine::createInstance() {
  std::vector<char const *> requiredLayers = getRequiredLayers();
  std::vector<char const *> extensions = getRequiredExtensions();

  constexpr VkApplicationInfo appInfo{.sType =
                                          VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                      .pApplicationName = APPLICATION_NAME,
                                      .applicationVersion = APPLICATION_VERSION,
                                      .pEngineName = "MadmanEngine",
                                      .engineVersion = VK_MAKE_VERSION(0, 1, 0),
                                      .apiVersion = VK_API_VERSION_1_0};

  VkInstanceCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appInfo,
      .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
      .ppEnabledLayerNames = requiredLayers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data()};

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan Instance");
  }

  LOGD("Instance created!");
};

void Engine::setPhysicalDevice() {
  // auto physicalDevices = instance.enumeratePhysicalDevices();
  //
  // if (physicalDevices.empty())
  //   throw std::runtime_error("Failed to find GPUs with vulkan support!");
  //
  // for (const auto &physicalDevice : physicalDevices) {
  //   if (isDeviceSupported(physicalDevice)) {
  //
  //   } else {
  //     continue;
  //   }
  // }
}

// bool Engine::isDeviceSupported(const vk::raii::PhysicalDevice
// &physicalDevice) {
//   return false;
// }
//====================================================================
//  Get Extensions and Layers
//====================================================================

std::vector<char const *> Engine::getRequiredLayers() {
  if constexpr (isDebug) {

    // const std::vector<char const *> validationLayers{
    //     "VK_LAYER_KHRONOS_validation"};
    // auto layerProperties = context.enumerateInstanceLayerProperties();
    //
    // for (const auto &validationLayer : validationLayers) {
    //   bool found = false;
    //
    //   for (const auto &layerProperty : layerProperties) {
    //     if (strcmp(validationLayer, layerProperty.layerName.data()) == 0) {
    //       found = true;
    //       break;
    //     }
    //   }
    //
    //   if (!found) {
    //     LOGE("Validation Layer %s not found.", validationLayer);
    //     return {};
    //   }
    // }
    // return validationLayers;
  }
  return {};
}

std::vector<char const *> Engine::getRequiredExtensions() {

  std::vector<char const *> extensions = {"VK_KHR_surface",
                                          "VK_KHR_android_surface"};

  // if constexpr (isDebug) {
  //   extensions.push_back(vk::EXTDebugUtilsExtensionName);
  // }

  return extensions;
}

//====================================================================
//  Engine State Controls
//====================================================================

void Engine::start() {
  if (isRunning)
    return;

  initVulkan();

  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);

  return;
}

void Engine::stop() {
  if (!isRunning)
    return;

  isRunning = false;

  if (renderThread.joinable()) {
    renderThread.join();
  }

  cleanupVulkan();
  return;
}

void Engine::resize(int h, int w) {
  height = h;
  width = w;

  LOGD("resized from cpp with dimentions %dx%d", height.load(), width.load());

  return;
}

//====================================================================
//  Engine Render Loop and Cleanup
//====================================================================

void Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (isRunning) {
    if (window != nullptr) {
    } else {
      LOGI("window is null");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");
}

void Engine::cleanupVulkan() { vkDestroyInstance(instance, nullptr); }
//====================================================================
//  Debug Functions
//====================================================================
// void Engine::setDebugMessenger() {
//
//   vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
//       vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
//       vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
//
//   vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
//       vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
//       vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
//       vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);
//
//   vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT(
//       {}, severityFlags, messageTypeFlags, &debugCallback);
//
//   debugMessenger =
//       instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
//
//   LOGD("Debug Messenger Initialized!");
// }
//
// VKAPI_ATTR VkBool32 VKAPI_CALL
// Engine::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
//                       VkDebugUtilsMessageTypeFlagsEXT messageType,
//                       const VkDebugUtilsMessengerCallbackDataEXT
//                       *pCallbackData, void *pUserData) {
//
//   auto cppType = static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(messageType);
//   std::string typeStr = vk::to_string(cppType);
//
//   auto cppSeverity =
//       static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity);
//
//   switch (cppSeverity) {
//   case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
//     LOGW("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
//     break;
//
//   case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
//     LOGE("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
//     break;
//
//   default:
//     LOGI("[%s]: %s", typeStr.c_str(), pCallbackData->pMessage);
//     break;
//   }
//
//   return VK_FALSE;
// }
