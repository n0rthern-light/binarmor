file(GLOB_RECURSE dll_SRC "*.cpp")

add_library(dll SHARED ${dll_SRC})

target_link_libraries(dll shared)
target_include_directories(dll PUBLIC ${SRC_INCLUDES})
