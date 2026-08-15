#pragma once

class NativeWindow {
public:
  NativeWindow(void *window) : window(window) {};
  ~NativeWindow() = default;

  void *window;
};
