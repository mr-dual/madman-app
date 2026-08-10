#pragma once

#include "engine/context/graphics/GraphicsContext.hpp"
#include <vector>
#include <vulkan/vulkan_core.h>

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  void createInstance();
  // bool isDeviceSupported(const vk::raii::PhysicalDevice &physicalDevice);

  // Debug Mode Stuff
  void setDebugMessenger();
  // static VKAPI_ATTR VkBool32 VKAPI_CALL
  // debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  //               VkDebugUtilsMessageTypeFlagsEXT messageType,
  //               const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
  //               void *pUserData);

  VkDebugUtilsMessengerCreateInfoEXT popuateDebugUtilsMessengerCreateInfoEXT();

public:
  VulkanContext() = default;
  ~VulkanContext() override { cleanup(); };

  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int h, int w) override;
};
