#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>

void createInstance(VkInstance &instance);
VkPhysicalDevice pickPhysicalDevice(VkInstance instance);
VkDevice createDevice(VkPhysicalDevice physicalDevice);

VkDebugUtilsMessengerCreateInfoEXT populateDebugUtilsMessengerCreateInfoEXT();
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance);

std::vector<char const *> getRequiredLayers();
std::vector<char const *>
getRequiredExtensions(std::vector<char const *> &layers);

struct QueueFamilyIndices {
  std::optional<uint32_t> grpahicsFamily;
  bool isComplete() { return grpahicsFamily.has_value(); }
};

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice device);
