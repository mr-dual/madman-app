#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <jni.h>

#define LOG_TAG "MadmanEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

// This function fires when your Kotlin EngineRenderView is placed on screen
JNIEXPORT void JNICALL Java_com_madman_engine_MadmanJni_initVulkan(
    JNIEnv *env, jobject thiz, jobject surface) {
  LOGI("Kotlin passed the surface to C++!");

  // Convert the Kotlin surface object into a raw hardware window pointer
  ANativeWindow *window = ANativeWindow_fromSurface(env, surface);

  if (window != nullptr) {
    LOGI("Native Window acquired successfully! Vulkan setup can safely start "
         "here.");
    // TODO: Pass 'window' to your Vulkan initialization functions
  } else {
    LOGI("Error: Native Window was null!");
  }
}

JNIEXPORT void JNICALL
Java_com_madman_engine_MadmanJni_stepFrame(JNIEnv *env, jobject thiz) {
  LOGI("Screen Rendering");
}

JNIEXPORT void JNICALL Java_com_madman_engine_MadmanJni_resizeVulkan(
    JNIEnv *env, jobject thiz, jint width, jint height) {
  LOGI("Screen resized to: %dx%d", width, height);
}

JNIEXPORT void JNICALL
Java_com_madman_engine_MadmanJni_terminateVulkan(JNIEnv *env, jobject thiz) {
  LOGI("Surface destroyed. Cleaning up Vulkan!");
}
}
