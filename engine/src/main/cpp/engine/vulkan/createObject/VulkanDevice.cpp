#include "engine/vulkan/VulkanContext.hpp"
#include "util/Log.hpp"
#include <cstdint>
#include <set>
#include <stdexcept>

void VulkanContext::createDevice() {

  if (!queueIndices.isComplete())
    throw std::range_error("No valid queue found!");

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> queueFamilies = {queueIndices.presentFamily.value(),
                                      queueIndices.graphicsFamily.value()};

  float queuePriority = 1.0f;
  for (uint32_t family : queueFamilies) {
    queueCreateInfos.push_back(VkDeviceQueueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = family,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority});
  }

  VkPhysicalDeviceFeatures deviceFeatures{};

  VkDeviceCreateInfo deviceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledLayerCount = 0,
      .enabledExtensionCount = 0,
      .pEnabledFeatures = &deviceFeatures};

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create logical device!");

  vkGetDeviceQueue(device, queueIndices.graphicsFamily.value(), 0,
                   &graphicsQueue);
  vkGetDeviceQueue(device, queueIndices.presentFamily.value(), 0,
                   &presentQueue);

  LOGD("Created logical device!");
}
