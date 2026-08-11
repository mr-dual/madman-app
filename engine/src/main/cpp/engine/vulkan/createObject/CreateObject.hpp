#pragma once

#include <vulkan/vulkan_core.h>

void createInstance(VkInstance &instance);
VkPhysicalDevice createPhysicalDevice(VkInstance instance);

VkDebugUtilsMessengerCreateInfoEXT populateDebugUtilsMessengerCreateInfoEXT();
VkDebugUtilsMessengerEXT createDebugMessenger(VkInstance instance);
