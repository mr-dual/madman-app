#include "CreateObject.hpp"
#include "platforms/GetExtensions.hpp"
#include "util/ApplicationInfo.hpp"
#include "util/IsDebug.hpp"
#include "util/Log.hpp"

#include <algorithm>
#include <cstring>
#include <ranges>
#include <span>
#include <string_view>
#include <vector>
namespace {

void verifyExtsAndLayers(std::span<const char *const> exts,
                         std::span<const char *const> layers);
}
//====================================================================
// Create Instance
//====================================================================

void createInstance(VkInstance &instance) {
  // Get and verify Layers And Extensions

  std::vector<char const *> validationLayers = getRequiredLayers();

  auto extensions = getExtensions();

  verifyExtsAndLayers(extensions, validationLayers);

  constexpr VkApplicationInfo appInfo{.sType =
                                          VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                      .pApplicationName = APPLICATION_NAME,
                                      .applicationVersion = APPLICATION_VERSION,
                                      .pEngineName = "MadmanEngine",
                                      .engineVersion = VK_MAKE_VERSION(0, 1, 0),
                                      .apiVersion = VK_API_VERSION_1_0};

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo =
      populateDebugUtilsMessengerCreateInfoEXT();

  VkInstanceCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = isDebug ? &debugCreateInfo : nullptr,
      .pApplicationInfo = &appInfo,
      .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
      .ppEnabledLayerNames = validationLayers.data(),
      .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data()};

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan Instance");
  }

  LOGD("Instance created!");
};

//====================================================================
//  Verify Layers and Extensions
//====================================================================
namespace {
void verifyExtsAndLayers(std::span<const char *const> exts,
                         std::span<const char *const> layers) {

  if constexpr (isDebug) {
    // Get Layers from Device.
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> devLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, devLayers.data());

    // Check if Layers are in Device
    bool layerSupported =
        std::ranges::all_of(layers, [&devLayers](std::string_view layer) {
          return std::ranges::any_of(
              devLayers,
              [&layer](std::string_view devLayer) { return devLayer == layer; },
              &VkLayerProperties::layerName);
        });

    if (!layerSupported) {
      throw std::runtime_error("Error: Layer missing");
    }
  }

  // Get Extensions from Device
  uint32_t extCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
  std::vector<VkExtensionProperties> devExts(extCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extCount, devExts.data());

  // Get Extensions from Layers and join them
  auto layerExts =
      layers | std::views::transform([](const auto &layer) {
        uint32_t layerExtCount = 0;
        vkEnumerateInstanceExtensionProperties(layer, &layerExtCount, nullptr);

        std::vector<VkExtensionProperties> layerExts(layerExtCount);
        vkEnumerateInstanceExtensionProperties(layer, &layerExtCount,
                                               layerExts.data());
        return layerExts;
      }) |
      std::views::join | std::views::common;

  devExts.insert(devExts.end(), layerExts.begin(), layerExts.end());

  // check if device supports extensions
  auto isSupported =
      std::ranges::all_of(exts, [&devExts](std::string_view ext) {
        return std::ranges::any_of(
            devExts, [ext](std::string_view dExt) { return ext == dExt; },
            &VkExtensionProperties::extensionName);
      });

  if (!isSupported) {
    throw std::runtime_error("Device Extensions not supported!");
  }
}
} // namespace
std::vector<char const *> getRequiredLayers() {
  if constexpr (isDebug)
    return {"VK_LAYER_KHRONOS_validation"};

  return {};
}
