#include "VulkanContext.hpp"
#include "createObject/createObject.hpp"
#include "debug/setDebugMessenger.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"
#include "utils/VulkanExtMethods.hpp"

#include <stdexcept>
#include <vulkan/vulkan.h>

namespace {
void setPhysicalDevice();
} // namespace

//====================================================================
// Initialize and Cleanup Vulkan .
//====================================================================

void VulkanContext::init() {
  if (instance != VK_NULL_HANDLE) {
    LOGD("Instance exists, skipping creation.");
  }

  try {
    createInstance(instance);
    if constexpr (isDebug)
      DebugMessenger::setDebugMessenger(instance, debugMessenger);
    setPhysicalDevice();

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

void VulkanContext::cleanup() {
  if (debugMessenger != VK_NULL_HANDLE) {
    vkMethods::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    debugMessenger = VK_NULL_HANDLE;
  }
  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
  }
}

void VulkanContext::resize(int h, int w) {
  // TODO:add resize stuff.
}

void VulkanContext::render() {
  // TODO:add render stuff.
}

namespace {
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
