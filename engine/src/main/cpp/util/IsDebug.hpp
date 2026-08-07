#pragma once

#ifdef NDEBUG
constexpr bool isDebug = false;
#else
constexpr bool isDebug = true;
#endif
