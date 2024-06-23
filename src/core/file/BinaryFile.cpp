#include "BinaryFile.hpp"
#include "core/attributes.hpp"
#include "core/file/BinaryAttributes.hpp"
#include "core/file/BinaryModification.hpp"
#include <stdexcept>

CBinaryFile::CBinaryFile(const std::string& filePath, const CBinary& binary, uint_32 flags, const BinaryAttributes_t& attributes): m_filePath(filePath), m_originalBinary(binary), m_flags(flags), m_attributes(attributes), m_vecBinaryModification({ })
{ }

std::filesystem::path CBinaryFile::filePath() const
{
    return m_filePath;
}

std::string CBinaryFile::fileName() const
{
    return m_filePath.filename().string();
}

file_id CBinaryFile::fileId() const
{
    return filePath().string();
}

CBinary CBinaryFile::originalBinary() const
{
    return m_originalBinary;
}

CBinary CBinaryFile::modifiedBinary() const
{
    auto modifiedBinary = m_originalBinary.bytes();

    for (const auto& modification : m_vecBinaryModification) {
        const auto& offset = modification.offset();
        const auto& size = modification.size();
        const auto& modificationBytes = modification.bytes();

        if (offset + size > modifiedBinary.size()) {
            modifiedBinary.resize(offset + size);
        }

        std::copy(modificationBytes.begin(), modificationBytes.end(), modifiedBinary.begin() + offset);
    }
    
    return CBinary { modifiedBinary };
}

Format CBinaryFile::format() const
{
    return m_attributes.format;
}

Architecture CBinaryFile::arch() const
{
    return m_attributes.arch;
}

BinaryAttributes_t CBinaryFile::attributes() const
{
    return m_attributes;
}

void CBinaryFile::enableFlags(BinaryFileFlags flags)
{
    m_flags |= static_cast<uint_32>(flags);
}

void CBinaryFile::disableFlags(BinaryFileFlags flags)
{
    m_flags &= ~static_cast<uint_32>(flags);
}

bool CBinaryFile::hasFlags(BinaryFileFlags flags) const
{
    if (flags == BinaryFileFlags::None && m_flags > 0) {
        return false;
    }

    return (m_flags & static_cast<uint_32>(flags)) == static_cast<uint_32>(flags);
}

bool CBinaryFile::hasAnyFlags() const
{
    return m_flags > 0;
}

bool CBinaryFile::isProtectedByBinarmor() const
{
    return m_attributes.isProtected;
}

bool CBinaryFile::hasModification(const CUuid& modificationId)
{
    for (const auto& modification : m_vecBinaryModification) {
        if (modification.id() == modificationId) {
            return true;
        }
    }

    return false;
}

void CBinaryFile::registerModification(const CBinaryModification& modification)
{
    if (hasModification(modification.id())) {
        throw std::runtime_error(strenc("Modification already registered"));
    }

    for (const auto& dependency : modification.requiredModificationIds()) {
        if (!hasModification(dependency)) {
            throw std::runtime_error(strenc("Modification requirements not met"));
        }
    }

    m_vecBinaryModification.push_back(modification);
}

