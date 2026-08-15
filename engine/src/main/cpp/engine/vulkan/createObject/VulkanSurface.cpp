#include "../VulkanExtMethods.hpp"
#include "CreateObject.hpp"

VkSurfaceKHR createSurface(VkInstance instance, NativeWindow window) {
  VkSurfaceKHR surface;

  VkAndroidSurfaceCreateInfoKHR createInfo{
      .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
      .window = static_cast<ANativeWindow *>(window.window)};

  if (vkMethods::CreateAndroidSurface(instance, &createInfo, nullptr,
                                      &surface) != VK_SUCCESS)
    throw std::runtime_error("Failed to create surface!");

  return surface;
}
