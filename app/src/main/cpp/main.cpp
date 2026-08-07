#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-text-input/gametextinput.h>

#define APPLICATION_NAME "MadmanApp"
#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 1
#define APP_VERSION_PATCH 0

#include "engine/2d/Engine2d.hpp"
#include "util/Log.hpp"

extern "C" {
//====================================================================
// Handle Window Initialization and Inputs
//====================================================================

void handleCmd(struct android_app *app, int32_t cmd) {
  switch (cmd) {
  case APP_CMD_INIT_WINDOW:
    // Native window is ready for rendering
    LOGD("APP_CMD_INIT_WINDOW received");
    break;
  case APP_CMD_TERM_WINDOW:
    // Clean up window resources here
    break;
  }
}

inline void initWindow(android_app *&app) {
  LOGD("Window initialized!");
  while (app->window == nullptr) {
    int events;
    android_poll_source *source;

    if (ALooper_pollOnce(-1, nullptr, &events, (void **)&source) >= 0) {
      if (source != nullptr) {
        source->process(app, source);
      }
    }
  }
}

inline bool handleInput(android_app *&app) {
  LOGD("Engine initialized");

  int events;
  android_poll_source *source;

  while (ALooper_pollOnce(0, nullptr, &events, (void **)&source) >= 0) {
    if (source != nullptr) {
      source->process(app, source);
    }

    if (app->destroyRequested != 0) {
      return false;
    }
  }
  return true;
}

//====================================================================
// Android Main
//====================================================================
void android_main(struct android_app *app) {
  LOGD("Madman Engine Started!");

  app->onAppCmd = handleCmd;

  initWindow(app);

  static Engine2d gEngine(app->window);
  gEngine.start();

  while (handleInput(app)) {
    continue;
  }

  gEngine.stop();
}
}
