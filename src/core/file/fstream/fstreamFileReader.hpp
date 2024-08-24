#ifndef CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_
#define CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_

#include "core/file/IFileSystem.hpp"

class CfstreamFileSystem : public IFileSystem
{
public:
    CBinary read(const std::string& filePath) const;
    void save(const CBinary& binary, const std::string& filePath) const;
    void remove(const std::string& filePath) const;
};

#endif // CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_
