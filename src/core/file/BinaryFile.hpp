#ifndef CORE_FILE__BINARY_FILE_HPP_
#define CORE_FILE__BINARY_FILE_HPP_

#include "../shared/Binary.hpp"
#include "../shared/attributes.hpp"
#include "BinaryFileAttributes.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/format/IFormat.hpp"
#include "flags.hpp"
#include "shared/value/Uuid.hpp"
#include <string>
#include <filesystem>

class CBinaryFile;
using file_id = std::string;
using binary_file_ptr = std::shared_ptr<CBinaryFile>;

class CBinaryFile
{
    const std::filesystem::path m_filePath;
    const CBinary m_originalBinary;
    std::vector<const CBinaryModification> m_vecBinaryModification;
    uint_32 m_flags;
    BinaryFileAttributes_t m_attributes;
public:
    CBinaryFile(const std::string& filePath, const CBinary& binary, uint_32 flags, const BinaryFileAttributes_t& attributes);
    std::filesystem::path filePath() const;
    std::string fileName() const;
    file_id fileId() const;
    CBinary originalBinary() const;
    CBinary modifiedBinary() const;
    std::shared_ptr<IFormat> modifiedBinaryAsFormat() const;
    Format format() const;
    Architecture arch() const;
    BinaryFileAttributes_t attributes() const;
    void enableFlags(BinaryFileFlags flags);
    void disableFlags(BinaryFileFlags flags);
    bool hasFlags(BinaryFileFlags flags) const;
    bool hasAnyFlags() const;
    bool isProtectedByBinarmor() const;
    bool hasModification(const CUuid& modificationId) const;
    std::shared_ptr<const CBinaryModification> modification(const CUuid& modificationId) const;
    void registerModification(const CBinaryModification& modification);
};

#endif // CORE_FILE__BINARY_FILE_HPP_
