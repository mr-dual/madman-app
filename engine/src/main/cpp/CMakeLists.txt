cmake_minimum_required(VERSION 3.22.1)
project("madman_engine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  VulkanHeaders
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
  GIT_TAG v1.3.275)
FetchContent_MakeAvailable(VulkanHeaders)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(madman_engine STATIC ${ENGINE_SOURCES})

find_program(GLSLC glslc REQUIRED)

file(GLOB SHADERS CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
     "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag")

set(SPIRV_OUTPUTS "")

foreach(SHADER ${SHADERS})
  get_filename_component(FILENAME ${SHADER} NAME)

  set(OUTPUT_SPV "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${FILENAME}.spv")

  add_custom_command(
    OUTPUT ${OUTPUT_SPV}
    COMMAND ${GLSLC} ${SHADER} -o ${OUTPUT_SPV}
    DEPENDS ${SHADER}
    COMMENT "Compiling SPIR-V: ${FILENAME}")

  list(APPEND SPIRV_OUTPUTS ${OUTPUT_SPV})
endforeach()

add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_OUTPUTS})

add_dependencies(madman_engine CompileShaders)

target_compile_options(madman_engine PRIVATE -ffunction-sections
                                             -fdata-sections)

target_include_directories(madman_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(madman_engine PRIVATE Vulkan::Headers vulkan android log)
