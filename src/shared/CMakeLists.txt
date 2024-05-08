file(GLOB_RECURSE shared_SRC "*.cpp")
add_library(shared ${shared_SRC})
target_include_directories(shared PUBLIC src/shared)
