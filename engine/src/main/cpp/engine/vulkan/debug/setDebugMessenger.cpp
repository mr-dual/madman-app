#include "../VulkanContext.hpp"
#include "../utils/VulkanExtMethods.hpp"
#include "util/Log.hpp"
#include <stdexcept>

//====================================================================
//  Debug Functions
//====================================================================
namespace {
VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
              void *pUserData) {

  switch (messageSeverity) {
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
    LOGI("[VERBOSE]: %s", pCallbackData->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    LOGI("[INFO]: %s", pCallbackData->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    LOGW("[WARNING]: %s", pCallbackData->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    LOGE("[ERROR]: %s", pCallbackData->pMessage);
    break;
  default:
    LOGI("[UNKNOWN]: %s", pCallbackData->pMessage);
    break;
  }

  return VK_FALSE;
}
} // namespace

void VulkanContext::setDebugMessenger() {
  auto createInfo = popuateDebugUtilsMessengerCreateInfoEXT();

  if (vkMethods::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
                                              &debugMessenger) != VK_SUCCESS) {
    throw std::runtime_error("Error: Faimed to create debug messenger!");
  }

  LOGD("Debug Messenger Initialized!");
}

VkDebugUtilsMessengerCreateInfoEXT
VulkanContext::popuateDebugUtilsMessengerCreateInfoEXT() {

  return VkDebugUtilsMessengerCreateInfoEXT{
      .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
      .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
      .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                     VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
                     VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
      .pfnUserCallback = debugCallback,
      .pUserData = nullptr};
}
