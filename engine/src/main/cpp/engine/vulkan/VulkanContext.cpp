#include "VulkanContext.hpp"
#include "VulkanExtMethods.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"

#include <exception>
//====================================================================
// Initialize Vulkan and setWindow
//====================================================================

void VulkanContext::init() {
  if (_instance != VK_NULL_HANDLE) {
    LOGD("Instance exists, skipping creation.");
  }

  try {
    createInstance();
    if constexpr (isDebug)
      createDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createDevice();
    createSwapchain();
    createImageViews();
    createGraphicsPipeline();

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

void VulkanContext::setWindow(const NativeWindow &win) { _window = win; }
//====================================================================
// Cleanup Vulkan
//====================================================================

void VulkanContext::cleanup() {
  for (const auto &view : _imageViews) {
    vkDestroyImageView(_device, view, nullptr);
  }
  if (_swapchain != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(_device, _swapchain, nullptr);
    _swapchain = VK_NULL_HANDLE;
  }
  if (_device != VK_NULL_HANDLE) {
    vkDestroyDevice(_device, nullptr);
    _device = VK_NULL_HANDLE;
  }
  if (_surface != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    _surface = VK_NULL_HANDLE;
  }
  if (_debugMessenger != VK_NULL_HANDLE) {
    vkMethods::DestroyDebugUtilsMessengerEXT(_instance, _debugMessenger,
                                             nullptr);
    _debugMessenger = VK_NULL_HANDLE;
  }
  if (_instance != VK_NULL_HANDLE) {
    vkDestroyInstance(_instance, nullptr);
    _instance = VK_NULL_HANDLE;
  }
}

void VulkanContext::resize(int h, int w) {
  // TODO:add resize stuff.
}

void VulkanContext::render() {
  // TODO:add render stuff.
}
