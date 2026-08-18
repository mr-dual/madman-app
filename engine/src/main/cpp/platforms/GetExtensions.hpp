#pragma once

#include <vector>

#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#endif

#include <vulkan/vulkan.h>

#define VK_BASE_EXTS VK_KHR_SURFACE_EXTENSION_NAME

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#define VK_PLATFORM_SURFACE_EXT VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#endif

std::vector<char const *> getExtensions();
std::vector<char const *> getDeviceExtensions();
