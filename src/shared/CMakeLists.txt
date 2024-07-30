file(GLOB_RECURSE shared_SRC "*.cpp")
add_library(shared ${shared_SRC})
target_include_directories(shared PUBLIC src/shared)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(shared OpenSSL::SSL OpenSSL::Crypto)

