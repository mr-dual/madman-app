#pragma once

#include "engine/context/graphics/GraphicsContext.hpp"
#include <vulkan/vulkan_core.h>

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  // VkDebugUtilsMessengerEXT debugMessenger = nullptr;
  VkPhysicalDevice physicalDevice = nullptr;

  // bool isDeviceSupported(const vk::raii::PhysicalDevice &physicalDevice);

  // Debug Mode Stuff
  // void setDebugMessenger();
  // static VKAPI_ATTR VkBool32 VKAPI_CALL
  // debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  //               VkDebugUtilsMessageTypeFlagsEXT messageType,
  //               const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
  //               void *pUserData);

public:
  VulkanContext() = default;
  ~VulkanContext() override = default;

  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int h, int w) override;
};
