#include "vulkan/vulkan_core.h"

//====================================================================
//  Debug Functions
//====================================================================
namespace DebugMessenger {
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);

VkDebugUtilsMessengerCreateInfoEXT popuateDebugUtilsMessengerCreateInfoEXT();

void setDebugMessenger(VkInstance &instance,
                       VkDebugUtilsMessengerEXT &debugMessenger);
} // namespace DebugMessenger
