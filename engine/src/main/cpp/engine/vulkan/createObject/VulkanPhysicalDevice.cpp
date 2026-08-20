#include "engine/vulkan/VulkanContext.hpp"
#include "platforms/GetExtensions.hpp"
#include "util/Log.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <utility>

//====================================================================
// Forward Declarations.
//====================================================================

namespace {
bool isDeviceExtensionsSupported(VkPhysicalDevice device);

SwapChainSupportDetails fetchSwapChainSupportDetails(VkPhysicalDevice device,
                                                     VkSurfaceKHR surface);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface);
int rateDevice(const VkPhysicalDevice device, QueueFamilyIndices &indices,
               VkSurfaceKHR surface, SwapChainSupportDetails &swapchainDetails);
} // namespace

//====================================================================
//  Pick Physical Device.
//====================================================================

void VulkanContext::pickPhysicalDevice() {

  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

  if (deviceCount == 0)
    throw std::runtime_error("Failed to find GPUs with vulkan support!");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

  std::multimap<int, std::tuple<VkPhysicalDevice, QueueFamilyIndices,
                                SwapChainSupportDetails>>
      candidates;
  for (const auto &physDevice : devices) {
    auto indices = findQueueFamilies(physDevice, _surface);
    auto swapchainDetail = fetchSwapChainSupportDetails(physDevice, _surface);

    candidates.insert(std::make_pair(
        rateDevice(physDevice, indices, _surface, swapchainDetail),
        std::tuple(physDevice, indices, swapchainDetail)));
  }

  if (candidates.rbegin()->first > 0) {
    auto [physicalDevice, queueIndices, swapchainDetails] =
        candidates.rbegin()->second;

    _physicalDevice = physicalDevice;
    _queueIndices = queueIndices;
    _swapChainDetails = swapchainDetails;

    LOGD("Physical Device Selected!");
  } else {
    throw std::runtime_error("Failed to find a suitable GPU!");
  }
}

namespace {

//====================================================================
// Rate Device
//====================================================================

int rateDevice(const VkPhysicalDevice device, QueueFamilyIndices &indices,
               VkSurfaceKHR surface,
               SwapChainSupportDetails &swapchainDetails) {
  int score = 0;

  // Fetch features and properties.
  VkPhysicalDeviceFeatures deviceFeatures;
  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  auto swapChainAdequate = !swapchainDetails.presentModes.empty() &&
                           !swapchainDetails.formats.empty();

  if (isDeviceExtensionsSupported(device) && indices.isComplete() &&
      swapChainAdequate) {
    score += 100;
  } else {
    return 0;
  }

  if (deviceProperties.apiVersion < VK_API_VERSION_1_0)
    return 0;

  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    score += 1000;

  return score;
}

//====================================================================
// Fetch Swapchain Support Details
//====================================================================

SwapChainSupportDetails fetchSwapChainSupportDetails(VkPhysicalDevice device,
                                                     VkSurfaceKHR surface) {
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
                                            &details.capabilities);

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
                                         details.formats.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount,
                                            nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        device, surface, &presentModeCount, details.presentModes.data());
  }

  return details;
}

//====================================================================
// Is Device Extensions Supported.
//====================================================================

bool isDeviceExtensionsSupported(VkPhysicalDevice device) {
  // Get Device Extensions
  std::vector<char const *> extensions = getDeviceExtensions();

  // Get Device Extensions from Device
  uint32_t extCount = 0;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extCount, nullptr);
  std::vector<VkExtensionProperties> devExts(extCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extCount,
                                       devExts.data());

  // check if device supports extensions
  auto isSupported =
      std::ranges::all_of(extensions, [&devExts](std::string_view ext) {
        return std::ranges::any_of(
            devExts, [ext](std::string_view dExt) { return ext == dExt; },
            &VkExtensionProperties::extensionName);
      });

  return isSupported;
}

//====================================================================
// Find Queue Families.
//====================================================================

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
    if (!indices.graphicsFamily.has_value() &&
        (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
      indices.graphicsFamily = i;
    }
    if (!indices.presentFamily.has_value() && presentSupport)
      indices.presentFamily = i;
    if (indices.isComplete())
      break;
  }

  return indices;
}
} // namespace
