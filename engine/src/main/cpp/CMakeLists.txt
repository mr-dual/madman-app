cmake_minimum_required(VERSION 3.22.1)
project("madman_engine")

add_library(madman_engine SHARED main.cpp)

target_link_libraries(madman_engine
    vulkan    # Vulkan Driver
    android   # Native display context
    log)      # Console output

