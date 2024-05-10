set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

file(GLOB_RECURSE TEST_FILES "core/*Test.cpp")
foreach(TEST_FILE ${TEST_FILES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} core GTest::gtest_main)
	target_include_directories(${TEST_NAME} PUBLIC ${SRC_INCLUDES})
	gtest_discover_tests(${TEST_NAME})
endforeach()

file(GLOB_RECURSE TEST_FILES "shared/*Test.cpp")
foreach(TEST_FILE ${TEST_FILES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} shared GTest::gtest_main)
	target_include_directories(${TEST_NAME} PUBLIC ${SRC_INCLUDES})
	gtest_discover_tests(${TEST_NAME})
endforeach()

file(GLOB_RECURSE TEST_FILES "loader/*Test.cpp")
foreach(TEST_FILE ${TEST_FILES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} loader_lib GTest::gtest_main)
	target_include_directories(${TEST_NAME} PUBLIC ${SRC_INCLUDES})
	gtest_discover_tests(${TEST_NAME})
endforeach()
