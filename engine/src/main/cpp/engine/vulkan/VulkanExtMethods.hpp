#pragma once

#include "vulkan/vulkan_core.h"
#include <vulkan/vulkan_android.h>

namespace vkMethods {
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT messenger,
                                   const VkAllocationCallbacks *pAllocator);
VkResult CreateAndroidSurface(VkInstance instance,
                              const VkAndroidSurfaceCreateInfoKHR *pCreateInfo,
                              const VkAllocationCallbacks *pAllocator,
                              VkSurfaceKHR *pSurface);
} // namespace vkMethods
