file(GLOB_RECURSE core_SRC "*.cpp")
add_library(core ${core_SRC})
target_link_libraries(core shared)
target_include_directories(core PUBLIC  ${SRC_INCLUDES})
