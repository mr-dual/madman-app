#pragma once

#include "engine/context/GraphicsContext.hpp"
#include "engine/vulkan/createObject/CreateObject.hpp"
#include "platforms/NativeWindow.hpp"
#include <vulkan/vulkan.h>

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  Queues queues;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;

  QueueFamilyIndices queueIndices;
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
