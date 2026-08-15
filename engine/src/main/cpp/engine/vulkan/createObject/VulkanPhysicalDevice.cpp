#include "CreateObject.hpp"

#include <cstdint>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
int rateDevice(const VkPhysicalDevice device, QueueFamilyIndices &indices);
} // namespace

//====================================================================
//  Set Physical Device
//====================================================================

VkPhysicalDevice pickPhysicalDevice(VkInstance instance,
                                    QueueFamilyIndices &indices) {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0)
    throw std::runtime_error("Failed to find GPUs with vulkan support!");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  std::multimap<int, VkPhysicalDevice> candidates;
  for (const auto &device : devices) {
    int score = rateDevice(device, indices);
    candidates.insert(std::make_pair(score, device));
  }

  if (candidates.rbegin()->first > 0) {
    return candidates.rbegin()->second;
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
} // namespace
