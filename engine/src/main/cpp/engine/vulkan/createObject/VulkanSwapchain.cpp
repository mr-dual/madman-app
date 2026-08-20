#include "engine/vulkan/VulkanContext.hpp"
#include "platforms/NativeWindow.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>

namespace {
VkSurfaceFormatKHR
pickSurfaceFormat(std::vector<VkSurfaceFormatKHR> &surfaceFormats);
VkPresentModeKHR pickPresentMode(std::vector<VkPresentModeKHR> &presentModes);
VkExtent2D pickSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                          NativeWindow &win);
} // namespace

void VulkanContext::createSwapchain() {
  auto surfaceFormat = pickSurfaceFormat(_swapChainDetails.formats);
  auto presentMode = pickPresentMode(_swapChainDetails.presentModes);
  _extent = pickSwapExtent(_swapChainDetails.capabilities, _window);

  uint32_t imageCount = _swapChainDetails.capabilities.minImageCount + 1;

  if (_swapChainDetails.capabilities.maxImageCount > 0 &&
      imageCount > _swapChainDetails.capabilities.maxImageCount)
    imageCount = _swapChainDetails.capabilities.maxImageCount;

  std::set<uint32_t> uniqueQueueFamilies = {
      _queueIndices.graphicsFamily.value(),
      _queueIndices.presentFamily.value()};

  std::vector<uint32_t> queueFamilyIndices(uniqueQueueFamilies.begin(),
                                           uniqueQueueFamilies.end());

  VkSwapchainCreateInfoKHR createInfo{
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface = _surface,
      .minImageCount = imageCount,
      .imageFormat = surfaceFormat.format,
      .imageColorSpace = surfaceFormat.colorSpace,
      .imageExtent = _extent,
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .imageSharingMode = uniqueQueueFamilies.size() > 1
                              ? VK_SHARING_MODE_CONCURRENT
                              : VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount =
          uniqueQueueFamilies.size() > 1
              ? static_cast<uint32_t>(queueFamilyIndices.size())
              : 0,
      .pQueueFamilyIndices =
          uniqueQueueFamilies.size() > 1 ? queueFamilyIndices.data() : nullptr,
      .preTransform = _swapChainDetails.capabilities.currentTransform,
      .compositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
      .presentMode = presentMode,
      .clipped = VK_TRUE,
      .oldSwapchain = VK_NULL_HANDLE};

  if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapchain) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create swapchain!");

  vkGetSwapchainImagesKHR(_device, _swapchain, &imageCount, nullptr);
  _swapChainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(_device, _swapchain, &imageCount,
                          _swapChainImages.data());

  _imageFormat = surfaceFormat.format;

  LOGD("Created Swapchain!");
}

namespace {
VkSurfaceFormatKHR
pickSurfaceFormat(std::vector<VkSurfaceFormatKHR> &surfaceFormats) {
  for (const auto &format : surfaceFormats) {
    if ((format.format == VK_FORMAT_B8G8R8A8_SRGB) &&
        (format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
      return format;
  }
  return surfaceFormats[0];
}

VkPresentModeKHR pickPresentMode(std::vector<VkPresentModeKHR> &presentModes) {
  for (const auto &mode : presentModes) {
    if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
      return VK_PRESENT_MODE_MAILBOX_KHR;
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D pickSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                          NativeWindow &win) {
  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    uint32_t w, h;

    getWindowSize(win, w, h);

    VkExtent2D extent{.width = std::clamp(w, capabilities.minImageExtent.width,
                                          capabilities.maxImageExtent.width),
                      .height =
                          std::clamp(h, capabilities.minImageExtent.height,
                                     capabilities.maxImageExtent.height)};

    return extent;
  }
}
} // namespace
