#pragma once

#include "context/GraphicsContext.hpp"
#include "platforms/NativeWindow.hpp"
#include "vulkan/vulkan_core.h"
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
  VkInstance _instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;
  VkSurfaceKHR _surface = VK_NULL_HANDLE;
  VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
  VkDevice _device = VK_NULL_HANDLE;

  // Queues
  VkQueue _graphicsQueue = VK_NULL_HANDLE;
  VkQueue _presentQueue = VK_NULL_HANDLE;
  QueueFamilyIndices _queueIndices;

  // Swapchain.
  VkSwapchainKHR _swapchain = VK_NULL_HANDLE;
  SwapChainSupportDetails _swapChainDetails;
  std::vector<VkImage> _swapChainImages;
  VkFormat _imageFormat;
  VkExtent2D _extent;
  std::vector<VkImageView> _imageViews;

  VkRenderPass _renderPass = VK_NULL_HANDLE;
  VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
  VkPipeline _graphicsPipeline = VK_NULL_HANDLE;

  NativeWindow _window = nullptr;

  void createInstance();
  void pickPhysicalDevice();
  void createDevice();
  void createSurface();
  void createSwapchain();
  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();

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
