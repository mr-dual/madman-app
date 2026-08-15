#pragma once

#include "platforms/NativeWindow.hpp"
#include "vulkan/vulkan_core.h"
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

void createInstance(VkInstance &instance);
VkPhysicalDevice pickPhysicalDevice(VkInstance instance);
VkDevice createDevice(VkPhysicalDevice physicalDevice, VkQueue &queue);
VkSurfaceKHR createSurface(VkInstance instance, NativeWindow window);

VkDebugUtilsMessengerCreateInfoEXT populateDebugUtilsMessengerCreateInfoEXT();
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance);
std::vector<char const *> getRequiredLayers();

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  bool isComplete() { return graphicsFamily.has_value(); }
};

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice device);
