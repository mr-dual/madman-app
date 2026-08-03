#pragma once

#include "../core/Engine.hpp"

class Engine2d : public Engine {
public:
  Engine2d(ANativeWindow *win) : Engine(win) {};
};
