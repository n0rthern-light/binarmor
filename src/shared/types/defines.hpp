#ifndef SHARED_TYPES_DEFINES_HPP_
#define SHARED_TYPES_DEFINES_HPP_

#include <cstdint>
#include <vector>

typedef std::uintptr_t uint_auto;
typedef uint8_t uint_8;
typedef uint16_t uint_16;
typedef uint32_t uint_32;
typedef uint64_t uint_64;

#ifndef as_32
#define as_32(t) static_cast<uint_32>(t)
#endif

#ifndef as_64
#define as_64(t) static_cast<uint_64>(t)
#endif

#ifndef as_auto
#define as_auto(t) static_cast<uint_auto>(t)
#endif

typedef size_t binary_offset;
typedef const unsigned char* byte_ptr;
typedef std::vector<unsigned char> byte_vec;

#endif // SHARED_TYPES_DEFINES_HPP_
