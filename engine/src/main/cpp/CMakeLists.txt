cmake_minimum_required(VERSION 3.22.1)
project("madman_engine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    VulkanHeaders
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG        v1.3.275 
)
FetchContent_MakeAvailable(VulkanHeaders)

add_library(madman_engine STATIC 
    engine/2d/Engine2d.cpp
    engine/3d/Engine3d.cpp
    engine/core/Engine.cpp)

target_compile_options(madman_engine PRIVATE -ffunction-sections -fdata-sections)

target_include_directories(madman_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(madman_engine
    PRIVATE
        Vulkan::Headers 
        vulkan          
        android
        log
)

