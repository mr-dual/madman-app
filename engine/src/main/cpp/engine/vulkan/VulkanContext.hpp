#pragma once

#include "engine/context/GraphicsContext.hpp"
#include <vulkan/vulkan_core.h>

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;

  // bool isDeviceSupported(const vk::raii::PhysicalDevice &physicalDevice);

public:
  VulkanContext() = default;
  ~VulkanContext() override { cleanup(); };

  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int h, int w) override;
};
