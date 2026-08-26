#include "engine/vulkan/VulkanContext.hpp"
#include "vulkan/vulkan_core.h"
#include <cstddef>
#include <stdexcept>

void VulkanContext::createFrameBuffers() {
  _framebuffers.resize(_imageViews.size());

  for (size_t i = 0; i < _imageViews.size(); ++i) {
    VkImageView attachents[] = {_imageViews[i]};

    VkFramebufferCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = _renderPass,
        .attachmentCount = 1,
        .pAttachments = attachents,
        .width = _extent.width,
        .height = _extent.height,
        .layers = 1};

    if (vkCreateFramebuffer(_device, &createInfo, nullptr, &_framebuffers[i]) !=
        VK_SUCCESS)
      throw std::runtime_error("Failed to create framebuffers!");
  }
}
