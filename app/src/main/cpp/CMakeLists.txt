cmake_minimum_required(VERSION 3.22.1)
project("app_main")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(game-activity REQUIRED CONFIG)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../../../engine/src/main/cpp" engine_build)

add_library(app_main SHARED
    main.cpp
)

target_link_libraries(app_main
    PRIVATE
        game-activity::game-activity_static
        madman_engine      
        vulkan 
        android 
        log
)
