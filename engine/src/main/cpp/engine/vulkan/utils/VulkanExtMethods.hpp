#pragma once

#include "vulkan/vulkan_core.h"

namespace vkMethods {
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT messenger,
                                   const VkAllocationCallbacks *pAllocator);

void popuateDebugUtilsMessengerCreateInfoEXT(
    VkDebugUtilsMessengerCreateInfoEXT &rCreateInfo,
    PFN_vkDebugUtilsMessengerCallbackEXT debugCallback);
} // namespace vkMethods
