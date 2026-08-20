#include "engine/vulkan/VulkanContext.hpp"
#include "vulkan/vulkan_core.h"
#include <stdexcept>

void VulkanContext::createImageViews() {
  _imageViews.resize(_swapChainImages.size());

  for (size_t i = 0; i < _swapChainImages.size(); ++i) {
    VkImageViewCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = _swapChainImages[i],
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = _imageFormat,
        .components = {.r = VK_COMPONENT_SWIZZLE_IDENTITY,
                       .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                       .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                       .a = VK_COMPONENT_SWIZZLE_IDENTITY},
        .subresourceRange = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                             .baseMipLevel = 0,
                             .levelCount = 1,
                             .baseArrayLayer = 0,
                             .layerCount = 1}

    };

    if (vkCreateImageView(_device, &createInfo, nullptr, &_imageViews[i]) !=
        VK_SUCCESS)
      throw std::runtime_error("Failed to create Image Views!");
  }
}
