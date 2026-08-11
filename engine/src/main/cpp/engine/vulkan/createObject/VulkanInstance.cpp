#include "CreateObject.hpp"
#include "util/ApplicationInfo.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"

#include <vector>

//====================================================================
// Create Instance
//====================================================================

void createInstance(VkInstance &instance) {
  // Get Layers And Extensions
  std::vector<char const *> requiredLayers = getRequiredLayers();
  std::vector<char const *> extensions = getRequiredExtensions(requiredLayers);

  constexpr VkApplicationInfo appInfo{.sType =
                                          VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                      .pApplicationName = APPLICATION_NAME,
                                      .applicationVersion = APPLICATION_VERSION,
                                      .pEngineName = "MadmanEngine",
                                      .engineVersion = VK_MAKE_VERSION(0, 1, 0),
                                      .apiVersion = VK_API_VERSION_1_0};

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

  VkInstanceCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .pApplicationInfo = &appInfo,
      .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
      .ppEnabledLayerNames = requiredLayers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data()};

  if constexpr (isDebug) {
    debugCreateInfo = populateDebugUtilsMessengerCreateInfoEXT();
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
  }

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan Instance");
  }

  LOGD("Instance created!");
};

//====================================================================
//  Get Layers
//====================================================================

std::vector<char const *> getRequiredLayers() {
  if constexpr (isDebug) {

    const std::vector<char const *> validationLayers{
        "VK_LAYER_KHRONOS_validation"};

    // Get Layers from Device.
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    // Check if Layers are in Device .
    for (const auto &validLayer : validationLayers) {
      bool found = false;

      for (const auto &layer : layers) {
        if (strcmp(validLayer, layer.layerName) == 0) {
          found = true;
          break;
        }
      }

      if (!found) {
        throw std::runtime_error(std::string("Error: Layer missing:") +
                                 validLayer);
      }
    }

    return validationLayers;
  }
  return {};
}

//====================================================================
//  Get Extensions
//====================================================================

std::vector<char const *>
getRequiredExtensions(std::vector<char const *> &layers) {

  std::vector<char const *> extensions = {VK_KHR_SURFACE_EXTENSION_NAME,
                                          "VK_KHR_android_surface"};

  // Get Extensions from Device.
  uint32_t extentionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);

  std::vector<VkExtensionProperties> deviceExtensions(extentionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount,
                                         deviceExtensions.data());

  // Get Extensions from layers.
  for (const auto &layer : layers) {
    uint32_t layerExtCount = 0;
    vkEnumerateInstanceExtensionProperties(layer, &layerExtCount, nullptr);

    std::vector<VkExtensionProperties> layerExtensions(layerExtCount);
    vkEnumerateInstanceExtensionProperties(layer, &layerExtCount,
                                           layerExtensions.data());

    // Add layerExtensions to deviceExtensions .
    deviceExtensions.reserve(deviceExtensions.size() + layerExtensions.size());

    deviceExtensions.insert(deviceExtensions.end(), layerExtensions.begin(),
                            layerExtensions.end());
  }

  if constexpr (isDebug) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  // check if device supports extensions .
  auto isSupported =
      std::ranges::all_of(extensions, [&deviceExtensions](const auto &ext) {
        return std::ranges::any_of(deviceExtensions, [ext](const auto &dExt) {
          return strcmp(dExt.extensionName, ext) == 0;
        });
      });

  if (!isSupported) {
    throw std::runtime_error("Device Extensions not supported!");
  }

  return extensions;
}
