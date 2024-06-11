#ifndef CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_
#define CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_

#include "../IFileReader.hpp"

class CfstreamFileReader : public IFileReader
{
public:
    const CBinary read(const std::string& filePath);
};

#endif // CORE_FILE_FSTREAM_FSTREAM_FILE_READER_HPP_
