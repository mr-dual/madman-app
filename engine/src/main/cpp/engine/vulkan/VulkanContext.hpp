#pragma once

#include "engine/context/GraphicsContext.hpp"
#include "platforms/NativeWindow.hpp"
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;
  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class VulkanContext : public GraphicsContext {
private:
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;

  VkQueue graphicsQueue = VK_NULL_HANDLE;
  VkQueue presentQueue = VK_NULL_HANDLE;
  QueueFamilyIndices queueIndices;

  SwapChainSupportDetails swapChainDetails;

  NativeWindow window = nullptr;

  void createInstance();
  void pickPhysicalDevice();
  void createDevice();
  void createSurface();

  // Debug Messenger
  VkDebugUtilsMessengerCreateInfoEXT populateDebugUtilsMessengerCreateInfoEXT();
  void createDebugMessenger();

public:
  VulkanContext() = default;

  void setWindow(const NativeWindow &win) override;
  void init() override;
  void render() override;
  void cleanup() override;
  void resize(int w, int h) override;
};
