#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-text-input/gametextinput.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>

#include "util/Log.hpp"

// Your native main entry point (replaces MainActivity.kt)
void android_main(struct android_app *app) {
  LOGI("Madman Engine Started!");

  // Wait for the window to be initialized by Android
  while (app->window == nullptr) {
    int events;
    struct android_poll_source *source;
    if (ALooper_pollOnce(-1, nullptr, &events, (void **)&source) >= 0) {
      if (source != nullptr) {
        source->process(app, source);
      }
    }
  }

  // Pass app->window (ANativeWindow*) straight to Vulkan surface creation!
  // VkAndroidSurfaceCreateInfoKHR createInfo{ ... };
  // createInfo.window = app->window;

  bool running = true;

  // Core Game Loop
  while (running) {
    // 1. Poll OS / Touch / Motion Events
    int events;
    struct android_poll_source *source;

    // Non-blocking poll (timeout = 0)
    while (ALooper_pollOnce(0, nullptr, &events, (void **)&source) >= 0) {
      if (source != nullptr) {
        source->process(app, source);
      }

      if (app->destroyRequested != 0) {
        running = false;
        break;
      }
    }

    // 2. Render Vulkan Frame
    // renderer.drawFrame();
  }
}
