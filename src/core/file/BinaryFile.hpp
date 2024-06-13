#ifndef CORE_FILE__BINARY_FILE_HPP_
#define CORE_FILE__BINARY_FILE_HPP_

#include "../Binary.hpp"
#include "../attributes.hpp"
#include "BinaryAttributes.hpp"
#include "flags.hpp"
#include <string>
#include <filesystem>

class CBinaryFile;
using file_id = std::string;
using binary_file_ptr = std::shared_ptr<CBinaryFile>;

class CBinaryFile
{
    const std::filesystem::path m_filePath;
    const CBinary m_binary;
    uint_32 m_flags;
    BinaryAttributes_t m_attributes;
public:
    CBinaryFile(const std::string& filePath, const CBinary& binary, uint_32 flags, const BinaryAttributes_t& attributes);
    std::filesystem::path filePath() const;
    std::string fileName() const;
    file_id fileId() const;
    CBinary binary() const;
    Format format() const;
    BinaryAttributes_t attributes() const;
    void enableFlags(BinaryFileFlags flags);
    void disableFlags(BinaryFileFlags flags);
    bool hasFlags(BinaryFileFlags flags) const;
    bool hasAnyFlags() const;
    bool isProtectedByBinarmor() const;
    void assignAttributes(const BinaryAttributes_t& attributes);
    void completeAnalysis();
};

#endif // CORE_FILE__BINARY_FILE_HPP_
