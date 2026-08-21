#include <android/asset_manager.h>
#include <vector>

std::vector<char> getAssets(AAssetManager *mngr, const char *filename);
