#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <atomic>
#include <chrono>
#include <jni.h>
#include <sys/types.h>
#include <thread>

#define LOG_TAG "MadmanEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

class Engine {
public:
  void setWindow(ANativeWindow *win) { window = win; }

  void start() {
    if (isRunning)
      return;
    isRunning = true;
    renderThread = std::thread(&Engine::renderLoop, this);
  }

  void stop() {
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

  void resize(int h, int w) {
    height = h;
    width = w;

    LOGI("resized from cpp with dimentions %dx%d", height.load(), width.load());
  }

private:
  ANativeWindow *window = nullptr;
  std::thread renderThread;
  std::atomic<bool> isRunning{false};
  std::atomic<int> height{0};
  std::atomic<int> width{0};

  void renderLoop() {
    LOGI("Render started in cpp.");

    while (isRunning) {
      if (window != nullptr) {
        LOGI("window isnt null");
      } else {
        LOGI("window is null");
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    LOGI("Render stopped in cpp.");
  }
};

static Engine gEngine;

extern "C" {

JNIEXPORT void JNICALL Java_com_madman_engine_MadmanJni_initialize(
    JNIEnv *env, jobject thiz, jobject surface) {
  ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
  LOGI("Kotlin passed the surface to C++!");
  gEngine.setWindow(window);
  gEngine.start();
}

JNIEXPORT void JNICALL Java_com_madman_engine_MadmanJni_resize(JNIEnv *env,
                                                               jobject thiz,
                                                               jint width,
                                                               jint height) {
  LOGI("Screen resized to: %dx%d", width, height);
  gEngine.resize(height, width);
}

JNIEXPORT void JNICALL
Java_com_madman_engine_MadmanJni_terminate(JNIEnv *env, jobject thiz) {
  LOGI("Surface destroyed. Cleaning up Vulkan!");
  gEngine.stop();
}
}
