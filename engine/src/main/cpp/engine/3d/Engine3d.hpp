#pragma once

#include "../core/Engine.hpp"

class Engine3d : public Engine {
public:
  Engine3d(ANativeWindow *win) : Engine(win) {};
};
