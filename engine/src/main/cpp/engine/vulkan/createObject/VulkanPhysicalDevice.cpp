#include "CreateObject.hpp"

#include <cstdint>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
int rateDevice(const VkPhysicalDevice device);
}

//====================================================================
//  Set Physical Device
//====================================================================

VkPhysicalDevice createPhysicalDevice(VkInstance instance) {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0)
    throw std::runtime_error("Failed to find GPUs with vulkan support!");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  std::multimap<int, VkPhysicalDevice> candidates;
  for (const auto &device : devices) {
    int score = rateDevice(device);
    candidates.insert(std::make_pair(score, device));
  }

  if (candidates.rbegin()->first > 0) {
    return candidates.rbegin()->second;
  } else {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}

namespace {
int rateDevice(const VkPhysicalDevice device) {
  int score = 0;
  VkPhysicalDeviceFeatures deviceFeatures;
  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    score += 1000;

  if (deviceProperties.apiVersion < VK_API_VERSION_1_0)
    return 0;

  return score;
}
} // namespace
