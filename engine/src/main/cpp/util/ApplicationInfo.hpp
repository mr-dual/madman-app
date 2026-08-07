#pragma once

#ifndef APPLICATION_NAME
#define APPLICATION_NAME "Madman"
#endif

#ifndef APP_VERSION_MAJOR
#define APP_VERSION_MAJOR 0
#endif

#ifndef APP_VERSION_MINOR
#define APP_VERSION_MINOR 1
#endif

#ifndef APP_VERSION_PATCH
#define APP_VERSION_PATCH 0
#endif

#ifndef APPLICATION_VERSION
#define APPLICATION_VERSION                                                    \
  VK_MAKE_VERSION(APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH)
#endif
