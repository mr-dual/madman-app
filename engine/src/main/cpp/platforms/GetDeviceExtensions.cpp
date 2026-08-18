#include "GetExtensions.hpp"

std::vector<char const *> getDeviceExtensions() {
  return {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
}
