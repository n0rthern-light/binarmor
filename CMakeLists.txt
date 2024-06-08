cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("BinArmor")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(${CMAKE_BINARY_DIR}/../Debug/generators/conan_toolchain.cmake)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    include(${CMAKE_BINARY_DIR}/../Release/generators/conan_toolchain.cmake)
else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

set(SRC_INCLUDES ${CMAKE_SOURCE_DIR}/src)

add_subdirectory ("src/shared")
add_subdirectory ("src/core")
add_subdirectory ("src/loader")
add_subdirectory ("tests")
