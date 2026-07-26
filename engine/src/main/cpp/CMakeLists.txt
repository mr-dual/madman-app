cmake_minimum_required(VERSION 3.22.1)
project("madman_engine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    VulkanHpp
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Hpp.git
    GIT_TAG        v1.3.275
)
FetchContent_MakeAvailable(VulkanHpp)

add_library(madman_engine SHARED
    main.cpp
    Engine.cpp
)

target_include_directories(madman_engine
    PRIVATE
        ${vulkanhpp_SOURCE_DIR}
        ${vulkanhpp_SOURCE_DIR}/vulkan
)

target_link_libraries(madman_engine
    PRIVATE
        vulkan          # Vulkan Driver (NDK)
        android         # Native display context
        log             # Console output
)

target_precompile_headers(madman_engine PRIVATE
    <vulkan/vulkan.hpp>
    <vulkan/vulkan_raii.hpp>
)

