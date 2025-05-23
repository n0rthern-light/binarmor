file(GLOB_RECURSE core_SRC "*.cpp")
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()
add_library(core ${core_SRC})

# shared
target_link_libraries(core shared)
target_include_directories(core PUBLIC ${SRC_INCLUDES})

# keystone
find_library(KEYSTONE_LIBRARY NAMES keystone)
include_directories(${KEYSTONE_INCLUDE_DIR})
target_link_libraries(core ${KEYSTONE_LIBRARY})

# capstone
find_library(CAPSTONE_LIBRARY NAMES capstone)
include_directories(${CAPSTONE_INCLUDE_DIR})
target_link_libraries(core ${CAPSTONE_LIBRARY})
