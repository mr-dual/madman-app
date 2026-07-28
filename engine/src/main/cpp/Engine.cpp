#include "Engine.hpp"
#include "util/Log.hpp"
#include <cstdint>
#include <vector>

const std::vector<char const *> validationLayers{"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

//====================================================================
// Lifecycle & Setup
//====================================================================

void Engine::setWindow(ANativeWindow *win) { window = win; }

void Engine::initVulkan() {

  if (*instance != nullptr) {
    LOGD("Instance exists, skipping creation.");
    return;
  }

  std::vector<char const *> requiredLayers;

  if (enableValidationLayers) {
    requiredLayers.assign(validationLayers.begin(), validationLayers.end());
  }

  auto layerProperties = context.enumerateInstanceLayerProperties();

  for (const auto &requiredLayer : requiredLayers) {
    bool found = false;

    for (const auto &layerProperty : layerProperties) {
      if (strcmp(requiredLayer, layerProperty.layerName.data()) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      LOGE("Validation Layer %s not found.", requiredLayer);
      return;
    }
  }

  try {
    constexpr vk::ApplicationInfo appInfo(
        "Madman", VK_MAKE_VERSION(0, 1, 0), "MadmanEngine",
        VK_MAKE_VERSION(0, 1, 0), vk::ApiVersion10);

    vk::InstanceCreateInfo createInfo(
        {}, &appInfo, static_cast<uint32_t>(requiredLayers.size()),
        requiredLayers.data());

    instance = vk::raii::Instance(context, createInfo);

    LOGD("Instance created!");

  } catch (const vk::SystemError &err) {
    LOGE("Vulkan System Error: %s at line %d", err.what(), err.code().value());

  } catch (const std::exception &err) {
    LOGE("Error: %s", err.what());
  }
}

//====================================================================
//  Engine State Controls
//====================================================================

void Engine::start() {
  if (isRunning)
    return;

  initVulkan();

  isRunning = true;
  renderThread = std::thread(&Engine::renderLoop, this);
}

void Engine::stop() {
  if (!isRunning)
    return;

  isRunning = false;

  if (renderThread.joinable()) {
    renderThread.join();
  }

  if (window) {
    ANativeWindow_release(window);
    window = nullptr;
  }
}

void Engine::resize(int h, int w) {
  height = h;
  width = w;

  LOGD("resized from cpp with dimentions %dx%d", height.load(), width.load());
}

//====================================================================
//  Engine Render Loop
//====================================================================

void Engine::renderLoop() {
  LOGD("Render started in cpp.");

  while (isRunning) {
    if (window != nullptr) {
    } else {
      LOGI("window is null");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  LOGD("Render stopped in cpp.");
}
