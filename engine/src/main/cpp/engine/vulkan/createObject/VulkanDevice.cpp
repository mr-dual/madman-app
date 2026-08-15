#include "CreateObject.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"

#include <cstdint>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>

VkDevice createDevice(VkPhysicalDevice physicalDevice,
                      QueueFamilyIndices &indices, Queues &queues) {
  VkDevice device;

  if (!indices.isComplete())
    throw std::range_error("No valid queue found!");

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> queueFamilies = {indices.presentFamily.value(),
                                      indices.graphicsFamily.value()};

  float queuePriority = 1.0f;
  for (uint32_t family : queueFamilies) {
    queueCreateInfos.push_back(VkDeviceQueueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = family,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority});
  }

  VkPhysicalDeviceFeatures deviceFeatures{};

  std::vector<const char *> layers = getRequiredLayers();

  VkDeviceCreateInfo deviceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledLayerCount = static_cast<uint32_t>(layers.size()),
      .ppEnabledLayerNames = layers.data(),
      .enabledExtensionCount = 0,
      .pEnabledFeatures = &deviceFeatures};

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create logical device!");

  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0,
                   &queues.graphicsQueue);
  vkGetDeviceQueue(device, indices.presentFamily.value(), 0,
                   &queues.presentQueue);

  LOGD("Created logical device!");
  return device;
}

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice device,
                                     const VkSurfaceKHR surface) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                           queueFamilies.data());

  LOGD("this device has %d queue families.",
       static_cast<int>(queueFamilies.size()));

  for (uint32_t i = 0; queueFamilies.size() > i; i++) {
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

    if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    if (presentSupport)
      indices.presentFamily = i;

    if (indices.isComplete())
      break;
  }

  return indices;
}
