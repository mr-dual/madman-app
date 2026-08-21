#include "GetAssets.hpp"
#include <cstddef>
#include <vector>

std::vector<char> getAssets(AAssetManager *mgr, const char *filename) {
  AAsset *asset = AAssetManager_open(mgr, filename, AASSET_MODE_BUFFER);
  if (!asset)
    return {};

  size_t size = AAsset_getLength(asset);
  std::vector<char> buffer(size);
  AAsset_read(asset, buffer.data(), size);
  AAsset_close(asset);

  return buffer;
}
