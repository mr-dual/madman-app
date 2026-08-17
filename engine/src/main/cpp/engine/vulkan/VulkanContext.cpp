#include "VulkanContext.hpp"
#include "VulkanExtMethods.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"

#include <exception>
//====================================================================
// Initialize Vulkan and setWindow
//====================================================================

void VulkanContext::init() {
  if (instance != VK_NULL_HANDLE) {
    LOGD("Instance exists, skipping creation.");
  }

  try {
    createInstance();
    if constexpr (isDebug)
      createDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createDevice();

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

void VulkanContext::setWindow(const NativeWindow &win) { window = win; }
//====================================================================
// Cleanup Vulkan
//====================================================================

void VulkanContext::cleanup() {
  if (device != VK_NULL_HANDLE) {
    vkDestroyDevice(device, nullptr);
    device = VK_NULL_HANDLE;
  }
  if (surface != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(instance, surface, nullptr);
    surface = VK_NULL_HANDLE;
  }
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
