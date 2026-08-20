#include "../VulkanExtMethods.hpp"
#include "engine/vulkan/VulkanContext.hpp"
#include "util/Log.hpp"

void VulkanContext::createSurface() {
  VkAndroidSurfaceCreateInfoKHR createInfo{
      .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
      .window = static_cast<ANativeWindow *>(_window.window)};

  if (vkMethods::CreateAndroidSurface(_instance, &createInfo, nullptr,
                                      &_surface) != VK_SUCCESS)
    throw std::runtime_error("Failed to create surface!");

  LOGD("Surface created!");
}
