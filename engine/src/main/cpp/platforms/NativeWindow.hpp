#pragma once

#include <cstdint>

class NativeWindow {
public:
  NativeWindow(void *window) : window(window) {};
  ~NativeWindow() = default;

  void *window;
};

void getWindowSize(NativeWindow &win, uint32_t &w, uint32_t &h);
