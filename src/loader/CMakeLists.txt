file(GLOB_RECURSE loader_SRC "*.cpp")
add_executable (loader WIN32 ${loader_SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET loader PROPERTY CXX_STANDARD 20)
endif()

set(wxWidgets_ROOT_DIR "C:/wxWidgets-3.2.4")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/vc_x64_lib")  # 64-bit
else()
  set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/vc_lib")      # 32-bit
endif()
set(wxWidgets_CONFIGURATION mswu)

find_package(wxWidgets REQUIRED core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

target_link_libraries(loader shared core ${wxWidgets_LIBRARIES})
target_include_directories(loader PUBLIC ${SRC_INCLUDES} ${wxWidgets_INCLUDE_DIRS})
add_definitions(-DWIN32_LEAN_AND_MEAN)

# static lib for testing
add_library(loader_lib ${loader_SRC})
target_link_libraries(loader_lib shared core ${wxWidgets_LIBRARIES})
target_include_directories(loader_lib PUBLIC ${SRC_INCLUDES} ${wxWidgets_INCLUDE_DIRS})
