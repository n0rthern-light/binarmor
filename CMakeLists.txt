cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("BinArmor")

set(SRC_INCLUDES ${CMAKE_SOURCE_DIR}/src)

add_subdirectory ("src/shared")
add_subdirectory ("src/core")
add_subdirectory ("src/loader")
add_subdirectory ("tests")
