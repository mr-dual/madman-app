#include "VulkanContext.hpp"
#include "util/ApplicationInfo.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace {
//====================================================================
//  Get Extensions and Layers
//====================================================================

std::vector<char const *> getRequiredLayers() {
  if constexpr (isDebug) {

    const std::vector<char const *> validationLayers{
        "VK_LAYER_KHRONOS_validation"};

    // Get Layers from Device.
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    // Check if Layers are in Device .
    for (const auto &validLayer : validationLayers) {
      bool found = false;

      for (const auto &layer : layers) {
        if (strcmp(validLayer, layer.layerName) == 0) {
          found = true;
          break;
        }
      }

      if (!found) {
        throw std::runtime_error(std::string("Error: Layer missing:") +
                                 validLayer);
      }
    }

    return validationLayers;
  }
  return {};
}

std::vector<char const *> getRequiredExtensions() {
  auto layers = getRequiredLayers();

  std::vector<char const *> extensions = {"VK_KHR_surface",
                                          "VK_KHR_android_surface"};

  // Get Extensions from Device.
  uint32_t extentionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);

  std::vector<VkExtensionProperties> deviceExtensions(extentionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount,
                                         deviceExtensions.data());

  for (const auto &layer : layers) {
    // Get Extensions from layers.
    uint32_t layerExtCount = 0;
    vkEnumerateInstanceExtensionProperties(layer, &layerExtCount, nullptr);

    std::vector<VkExtensionProperties> layerExtensions(layerExtCount);
    vkEnumerateInstanceExtensionProperties(layer, &layerExtCount,
                                           layerExtensions.data());

    // Add layerExtensions to deviceExtensions .
    deviceExtensions.reserve(deviceExtensions.size() + layerExtensions.size());

    deviceExtensions.insert(deviceExtensions.end(), layerExtensions.begin(),
                            layerExtensions.end());
  }

  if constexpr (isDebug) {
    extensions.push_back("VK_EXT_debug_utils");
  }

  // check if device supports extensions .
  auto isSupported =
      std::ranges::all_of(extensions, [&deviceExtensions](const auto &ext) {
        return std::ranges::any_of(deviceExtensions, [ext](const auto &dExt) {
          return strcmp(dExt.extensionName, ext) == 0;
        });
      });

  if (!isSupported) {
    throw std::runtime_error("Device Extensions not supported!");
  }

  return extensions;
}

//====================================================================
// Create Instance
//====================================================================

void createInstance(VkInstance &instance) {
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

//====================================================================
//  Set Physical Device
//====================================================================

void setPhysicalDevice() {
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
} // namespace

//====================================================================
// Initialize and Cleanup Vulkan
//====================================================================

void VulkanContext::init() {
  if (instance != VK_NULL_HANDLE) {
    LOGD("Instance exists, skipping creation.");
  }

  try {
    createInstance(instance);
    if constexpr (isDebug)
      setDebugMessenger();
    setPhysicalDevice();

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}
void VulkanContext::cleanup() {
  if (instance == VK_NULL_HANDLE)
    return;

  vkDestroyInstance(instance, nullptr);
  instance = VK_NULL_HANDLE;
}
void VulkanContext::resize(int h, int w) {
  // TODO:add resize stuff.
}

void VulkanContext::render() {
  // TODO:add render stuff.
}
//====================================================================
//  Debug Functions
//====================================================================
void VulkanContext::setDebugMessenger() {
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
}

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
