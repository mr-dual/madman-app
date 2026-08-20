#include "engine/vulkan/VulkanContext.hpp"
#include "platforms/GetExtensions.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <set>
#include <stdexcept>

void VulkanContext::createDevice() {

  if (!_queueIndices.isComplete())
    throw std::range_error("No valid queue found!");

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> queueFamilies = {_queueIndices.presentFamily.value(),
                                      _queueIndices.graphicsFamily.value()};

  float queuePriority = 1.0f;
  for (uint32_t family : queueFamilies) {
    queueCreateInfos.push_back(VkDeviceQueueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = family,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority});
  }

  VkPhysicalDeviceFeatures deviceFeatures{};

  std::vector<char const *> deviceExtensions = getDeviceExtensions();

  VkDeviceCreateInfo deviceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
      .ppEnabledExtensionNames = deviceExtensions.data(),
      .pEnabledFeatures = &deviceFeatures};

  if (vkCreateDevice(_physicalDevice, &deviceCreateInfo, nullptr, &_device) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create logical device!");

  vkGetDeviceQueue(_device, _queueIndices.graphicsFamily.value(), 0,
                   &_graphicsQueue);
  vkGetDeviceQueue(_device, _queueIndices.presentFamily.value(), 0,
                   &_presentQueue);

  LOGD("Created logical device!");
}
