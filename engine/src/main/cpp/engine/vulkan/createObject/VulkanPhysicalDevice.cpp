#include "engine/vulkan/VulkanContext.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <utility>

namespace {
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface);
int rateDevice(const VkPhysicalDevice device, QueueFamilyIndices &indices);
} // namespace

//====================================================================
//  Set Physical Device
//====================================================================

void VulkanContext::pickPhysicalDevice() {

  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0)
    throw std::runtime_error("Failed to find GPUs with vulkan support!");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  std::multimap<int, std::pair<VkPhysicalDevice, QueueFamilyIndices>>
      candidates;
  for (const auto &physDevice : devices) {
    auto indices = findQueueFamilies(physDevice, surface);

    candidates.insert(std::make_pair(rateDevice(physDevice, indices),
                                     std::make_pair(physDevice, indices)));
  }

  if (candidates.rbegin()->first > 0) {
    physicalDevice = candidates.rbegin()->second.first;
    queueIndices = candidates.rbegin()->second.second;

    LOGD("Physical Device Selected!");
  } else {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}

namespace {
int rateDevice(const VkPhysicalDevice device, QueueFamilyIndices &indices) {
  int score = 0;
  VkPhysicalDeviceFeatures deviceFeatures;
  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  if (!indices.isComplete()) {
    return 0;
  } else {
    score += 100;
  }

  if (deviceProperties.apiVersion < VK_API_VERSION_1_0)
    return 0;

  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    score += 1000;

  return score;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice,
                                     VkSurfaceKHR surface) {
  auto indices = QueueFamilyIndices{};

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                           nullptr);
  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                           queueFamilies.data());

  LOGD("this device has %d queue families.",
       static_cast<int>(queueFamilies.size()));

  for (uint32_t i = 0; queueFamilies.size() > i; i++) {
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface,
                                         &presentSupport);
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
} // namespace
