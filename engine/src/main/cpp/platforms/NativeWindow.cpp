#include "NativeWindow.hpp"

#ifdef __ANDROID__
#include <android/native_window.h>

void getWindowSize(NativeWindow &win, uint32_t &w, uint32_t &h) {
  w = ANativeWindow_getWidth((ANativeWindow *)win.window);
  h = ANativeWindow_getHeight((ANativeWindow *)win.window);
}
#endif
