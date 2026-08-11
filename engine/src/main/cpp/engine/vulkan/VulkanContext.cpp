#include "VulkanContext.hpp"
#include "VulkanExtMethods.hpp"
#include "createObject/CreateObject.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"

#include <exception>
#include <vulkan/vulkan.h>
//====================================================================
// Initialize Vulkan
//====================================================================

void VulkanContext::init() {
  if (instance != VK_NULL_HANDLE) {
    LOGD("Instance exists, skipping creation.");
  }

  try {
    createInstance(instance);
    if constexpr (isDebug)
      debugMessenger = createDebugMessenger(instance);
    physicalDevice = createPhysicalDevice(instance);

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

//====================================================================
// Cleanup Vulkan
//====================================================================

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
