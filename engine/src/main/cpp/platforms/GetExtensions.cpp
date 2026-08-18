#include "GetExtensions.hpp"
#include "util/IsDebug.hpp"
#include <vector>

std::vector<char const *> getExtensions() {
  auto ext = std::vector{VK_BASE_EXTS, VK_PLATFORM_SURFACE_EXT};

  if constexpr (isDebug)
    ext.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return ext;
}
