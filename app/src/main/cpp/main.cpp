#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-text-input/gametextinput.h>

#define APPLICATION_NAME "MadmanApp"
#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 1
#define APP_VERSION_PATCH 0

#include "engine/context/EngineContext.hpp"
#include "engine/model/Engine2d.hpp"
#include "util/Log.hpp"

//====================================================================
// Handle Inputs and Commands
//====================================================================

void handleCmd(struct android_app *app, int32_t cmd) {
  auto *engine = static_cast<Engine2d *>(app->userData);

  switch (cmd) {
  case APP_CMD_INIT_WINDOW:
    LOGD("APP_CMD_INIT_WINDOW received");
    engine->setWindow(app->window);
    engine->start();
    break;

  case APP_CMD_TERM_WINDOW:
    LOGD("APP_CMD_TERM_WINDOW received");
    engine->stopRender();
    break;

  case APP_CMD_CONFIG_CHANGED:
    LOGD("APP_CMD_CONFIG_CHANGED received");
    if (app->window != nullptr) {
      engine->resize(ANativeWindow_getHeight(app->window),
                     ANativeWindow_getWidth(app->window));
    }
    break;

  case APP_CMD_DESTROY:
    LOGD("APP_CMD_DESTROY received");
    engine->stopPhysics();
    engine->stopRender();
    break;
  }
}

inline bool handleInput(android_app *&app) {
  int events;
  android_poll_source *source;
  auto *engine = static_cast<Engine2d *>(app->userData);

  while (ALooper_pollOnce(app->window == nullptr ? -1 : 0, nullptr, &events,
                          (void **)&source) >= 0) {
    if (source != nullptr) {
      source->process(app, source);
    }

    if (app->destroyRequested != 0) {
      engine->stopPhysics();
      engine->stopRender();
      return false;
    }
  }
  return true;
}

//====================================================================
// Android Main
//====================================================================
extern "C" void android_main(struct android_app *app) {
  LOGD("Madman Engine Started!");

  EngineContext gEngineContext(240.0);
  Engine2d gEngine(gEngineContext);

  app->userData = &gEngine;
  app->onAppCmd = handleCmd;

  while (handleInput(app)) {
    continue;
  }
}
