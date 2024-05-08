file(GLOB_RECURSE dll_SRC "*.cpp")

add_library(dll SHARED ${dll_SRC})

target_link_libraries(dll ${wxWidgets_LIBRARIES} shared)
target_include_directories(dll PUBLIC ${wxWidgets_INCLUDE_DIRS})
