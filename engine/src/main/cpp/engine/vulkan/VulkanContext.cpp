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
    return;
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
    createRenderPass();
    createGraphicsPipeline();

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
    cleanup();
  }
}

void VulkanContext::setWindow(const NativeWindow &win) { _window = win; }
//====================================================================
// Cleanup Vulkan
//====================================================================

void VulkanContext::cleanup() {
  if (_device != VK_NULL_HANDLE) {
    if (_pipelineLayout != VK_NULL_HANDLE) {
      vkDestroyPipelineLayout(_device, _pipelineLayout, nullptr);
      _pipelineLayout = VK_NULL_HANDLE;
    }

    if (_renderPass != VK_NULL_HANDLE) {
      vkDestroyRenderPass(_device, _renderPass, nullptr);
      _renderPass = VK_NULL_HANDLE;
    }

    for (const auto &view : _imageViews) {
      if (view != VK_NULL_HANDLE)
        vkDestroyImageView(_device, view, nullptr);
    }
    _imageViews.clear();

    if (_swapchain != VK_NULL_HANDLE) {
      vkDestroySwapchainKHR(_device, _swapchain, nullptr);
      _swapchain = VK_NULL_HANDLE;
    }

    vkDestroyDevice(_device, nullptr);
    _device = VK_NULL_HANDLE;
  }

  if (_instance != VK_NULL_HANDLE) {
    if (_surface != VK_NULL_HANDLE) {
      vkDestroySurfaceKHR(_instance, _surface, nullptr);
      _surface = VK_NULL_HANDLE;
    }
    if (_debugMessenger != VK_NULL_HANDLE) {
      vkMethods::DestroyDebugUtilsMessengerEXT(_instance, _debugMessenger,
                                               nullptr);
      _debugMessenger = VK_NULL_HANDLE;
    }
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
