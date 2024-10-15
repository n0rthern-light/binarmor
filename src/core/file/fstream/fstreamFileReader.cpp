#include "fstreamFileReader.hpp"
#include <fstream>
#include <vector>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

using namespace program::core::file::fstream;

CBinary CfstreamFileSystem::read(const std::string& filePath) const
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

void CfstreamFileSystem::save(const CBinary& binary, const std::string& filePath) const
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw RuntimeException(strenc("Cannot open file for writing: ") + filePath);
    }

    const auto data = binary.bytes();
    if (!file.write(reinterpret_cast<const char*>(data.data()), data.size())) {
        throw RuntimeException(strenc("Failed to write the entire file."));
    }
}

void CfstreamFileSystem::remove(const std::string& filePath) const
{
    if (std::remove(filePath.c_str()) != 0) {
        throw RuntimeException(strenc("Failed to delete file: ") + filePath);
    }
}
