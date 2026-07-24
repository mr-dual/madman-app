cmake_minimum_required(VERSION 3.22.1)
project("madman_engine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(madman_engine SHARED
    main.cpp
    Engine.cpp
)

target_precompile_headers(madman_engine PRIVATE
    <vulkan/vulkan.hpp>
    <vulkan/vulkan_raii.hpp>
)

target_link_libraries(madman_engine
    vulkan    # Vulkan Driver
    android   # Native display context
    log)      # Console output

