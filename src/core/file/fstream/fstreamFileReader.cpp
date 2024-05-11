#include "fstreamFileReader.hpp"
#include <fstream>
#include <vector>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

const CBinary CfstreamFileReader::read(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw RuntimeException(strenc("Cannot open file: ") + filePath);
    }

    file.seekg(0, std::ios::end);
    std::size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        throw RuntimeException(strenc("Failed to read the entire file."));
    }

    return CBinary(buffer);
}
