#ifndef CORE_FILE_FLAGS_HPP_
#define CORE_FILE_FLAGS_HPP_

enum class BinaryFileFlags : unsigned int {
    NONE = 0,
    HAS_ENCRYPTED_ORIGINAL_IMPORTS = 1,
    HAS_MAIN_PROTECTION_SECTION_INITIALIZED = 2
};

#endif // CORE_FILE_FLAGS_HPP_
