#ifndef CORE_FILE__I_FILE_READER_HPP_
#define CORE_FILE__I_FILE_READER_HPP_

#include <string>
#include "../shared/Binary.hpp"

namespace program::core::file {
    class IFileSystem
    {
    public:
        virtual ~IFileSystem() {};
        virtual CBinary read(const std::string& filePath) const = 0;
        virtual void save(const CBinary& binary, const std::string& filePath) const = 0;
        virtual void remove(const std::string& filePath) const = 0;
    };
}

#endif // CORE_FILE__I_FILE_READER_HPP_
