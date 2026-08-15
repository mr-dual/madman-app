#include "VulkanExtMethods.hpp"
#include "util/Log.hpp"

namespace vkMethods {
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");

  if (func != nullptr)
    return func(instance, pCreateInfo, pAllocator, pMessenger);

  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT messenger,
                                   const VkAllocationCallbacks *pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");

  if (func != nullptr) {
    func(instance, messenger, pAllocator);
  } else {
    LOGE("Error: Couldn't find Destroy Debug Messenger");
  }
}

VkResult CreateAndroidSurface(VkInstance instance,
                              const VkAndroidSurfaceCreateInfoKHR *pCreateInfo,
                              const VkAllocationCallbacks *pAllocator,
                              VkSurfaceKHR *pSurface) {
  auto func = (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(
      instance, "vkCreateAndroidSurfaceKHR");

  if (func != nullptr)
    return func(instance, pCreateInfo, pAllocator, pSurface);

  return VK_ERROR_EXTENSION_NOT_PRESENT;
}
} // namespace vkMethods
