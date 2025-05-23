﻿file(GLOB_RECURSE loader_SRC "*.cpp")

set(_wxWidgets_ROOT_DIR "" CACHE STRING "Host's wxWidgets root path")
set(_wxWidgets_WX_CONFIG "" CACHE STRING "Relative from wxWidgets root path, the wx-config path")
set(_wxWidgets_LIB_X64 "" CACHE STRING "Relative from wxWidgets root path, the 32bit lib path")
set(_wxWidgets_LIB_X86 "" CACHE STRING "Relative from wxWidgets root path, the 64bit lib path")

set(wxWidgets_CONFIGURATION "" CACHE STRING "wxWidgets configuration (osx_cocoa|mswu fe.)")

if(WIN32)
	set(_wxWidgets_WX_RC "" CACHE STRING "Relative, from wxWidgets root path, the wx.rc path")
	add_executable (loader WIN32 ${loader_SRC} "${_wxWidgets_ROOT_DIR}${_wxWidgets_WX_RC}")
elseif(APPLE)
add_executable (loader MACOSX_BUNDLE ${loader_SRC})
set_target_properties(loader PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.loader
    MACOSX_BUNDLE_BUNDLE_NAME loader
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    #MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/customtemplate.plist.in
)
else()
add_executable (loader ${loader_SRC})
endif()



if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
  set(wxWidgets_LIB_DIR "${_wxWidgets_ROOT_DIR}${_wxWidgets_LIB_X64}")
else() # 32-bit
  set(wxWidgets_LIB_DIR "${_wxWidgets_ROOT_DIR}${_wxWidgets_LIB_X86}")
endif()

set(wxWidgets_CONFIG_EXECUTABLE "${_wxWidgets_ROOT_DIR}${_wxWidgets_WX_CONFIG}")

message(STATUS "_wxWidgets_ROOT_DIR: ${_wxWidgets_ROOT_DIR}")
message(STATUS "_wxWidgets_WX_CONFIG: ${_wxWidgets_WX_CONFIG}")
message(STATUS "wxWidgets_LIB_DIR: ${wxWidgets_LIB_DIR}")
message(STATUS "wxWidgets_CONFIGURATION: ${wxWidgets_CONFIGURATION}")
message(STATUS "wxWidgets_EXCLUDE_COMMON_LIBRARIES: ${wxWidgets_EXCLUDE_COMMON_LIBRARIES}")
message(STATUS "wxWidgets_CONFIG_EXECUTABLE: ${wxWidgets_CONFIG_EXECUTABLE}")

find_package(wxWidgets REQUIRED core base OPTIONAL_COMPONENTS net)

message(STATUS "wxWidgets is found: ${wxWidgets_FOUND}")
message(STATUS "wxWidgets_INCLUDE_DIRS: ${wxWidgets_INCLUDE_DIRS}")
message(STATUS "wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")
message(STATUS "wxWidgets_CXX_FLAGS: ${wxWidgets_CXX_FLAGS}")

include(${wxWidgets_USE_FILE})

target_link_libraries(loader shared core ${wxWidgets_LIBRARIES})
target_include_directories(loader PUBLIC ${SRC_INCLUDES} ${wxWidgets_INCLUDE_DIRS})
add_definitions(-DWIN32_LEAN_AND_MEAN)

# static lib for testing
# Exclude main.cpp from the list since its for tests
list(FILTER loader_SRC EXCLUDE REGEX ".*/main.cpp$")
add_library(loader_lib ${loader_SRC})
target_link_libraries(loader_lib shared core ${wxWidgets_LIBRARIES})
target_include_directories(loader_lib PUBLIC ${SRC_INCLUDES} ${wxWidgets_INCLUDE_DIRS})
