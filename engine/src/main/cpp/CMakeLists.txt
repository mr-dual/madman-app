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

add_library(madman_engine SHARED
    main.cpp
    Engine.cpp
)

target_link_libraries(madman_engine
    PRIVATE
        Vulkan::Headers 
        vulkan          
        android
        log
)

target_precompile_headers(madman_engine PRIVATE
    <vulkan/vulkan.hpp>
    <vulkan/vulkan_raii.hpp>
)

