#pragma once

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

struct Queues {
  VkQueue graphicsQueue;
  VkQueue presentQueue;
};

void createInstance(VkInstance &instance);
VkPhysicalDevice pickPhysicalDevice(VkInstance instance);
VkDevice createDevice(VkPhysicalDevice physicalDevice,
                      QueueFamilyIndices &indices, Queues &queues);
VkSurfaceKHR createSurface(VkInstance instance, NativeWindow window);

VkDebugUtilsMessengerCreateInfoEXT populateDebugUtilsMessengerCreateInfoEXT();
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance);
std::vector<char const *> getRequiredLayers();

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice device,
                                     const VkSurfaceKHR surface);
