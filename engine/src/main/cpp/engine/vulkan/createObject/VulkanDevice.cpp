#include "CreateObject.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <vector>

VkDevice createDevice(VkPhysicalDevice physicalDevice, VkQueue &queue) {
  VkDevice device;
  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  if (!indices.isComplete())
    throw std::range_error("No valid queue found!");

  float queuePriority = 1.0f;
  VkDeviceQueueCreateInfo queueCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueFamilyIndex = indices.graphicsFamily.value(),
      .queueCount = 1,
      .pQueuePriorities = &queuePriority};

  VkPhysicalDeviceFeatures deviceFeatures{};

  std::vector<const char *> layers = getRequiredLayers();

  VkDeviceCreateInfo deviceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &queueCreateInfo,
      .enabledLayerCount = static_cast<uint32_t>(layers.size()),
      .ppEnabledLayerNames = layers.data(),
      .enabledExtensionCount = 0,
      .pEnabledFeatures = &deviceFeatures};

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create logical device!");

  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &queue);

  LOGD("Created logical device!");
  return device;
}

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                           queueFamilies.data());

  for (uint32_t i = 0; queueFamilies.size() > i; i++) {
    if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
      break;
    }
  }

  return indices;
}
