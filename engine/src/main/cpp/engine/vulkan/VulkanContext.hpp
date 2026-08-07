#pragma once

#include "engine/graphicsContext/GraphicsContext.hpp"
#include <vulkan/vulkan_core.h>

class VulkanContext : public GraphicsContext {
public:
  VulkanContext() = default;
  ~VulkanContext() override = default;

  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int h, int w) override;

private:
  VkInstance instance = VK_NULL_HANDLE;
  // VkDebugUtilsMessengerEXT debugMessenger = nullptr;
  VkPhysicalDevice physicalDevice = nullptr;
};
