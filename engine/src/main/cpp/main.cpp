#include "Engine.hpp"
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <jni.h>
#include <sys/types.h>

#define LOG_TAG "MadmanEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static Engine gEngine;

extern "C" {

JNIEXPORT void JNICALL Java_com_madman_engine_MadmanJni_initialize(
    JNIEnv *env, jobject thiz, jobject surface) {
  ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
  LOGI("Kotlin passed the surface to C++!");
  gEngine.setWindow(window).start();
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
