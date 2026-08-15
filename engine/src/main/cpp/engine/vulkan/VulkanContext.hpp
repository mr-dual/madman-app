#pragma once

#include "engine/context/GraphicsContext.hpp"
#include "platforms/NativeWindow.hpp"
#include <vulkan/vulkan.h>

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  VkQueue queue = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;

  NativeWindow window = nullptr;

  // bool isDeviceSupported(const vk::raii::PhysicalDevice &physicalDevice);

public:
  VulkanContext() = default;

  void setWindow(const NativeWindow &win) override;
  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int w, int h) override;
};
