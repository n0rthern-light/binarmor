#include "BinaryFile.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/resize/BinarySizeChangedEvent.hpp"
#include "core/shared/attributes.hpp"
#include "core/file/BinaryFileAttributes.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/message/IMessageBus.hpp"
#include "shared/value/Uuid.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace program::core::file;
using namespace program::core::format;
using namespace program::core::shared;

CBinaryFile::CBinaryFile(
    IMessageBus* eventBus,
    const std::string& filePath,
    const CBinary& binary,
    uint_32 flags,
    const BinaryFileAttributes_t& attributes
):
    m_eventBus(eventBus),
    m_filePath(filePath),
    m_originalBinary(binary),
    m_flags(flags),
    m_attributes(attributes),
    m_vecBinaryModification({ })
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
    auto appliedModifications = std::vector<CUuid> { };

    for (const auto& modification : m_vecBinaryModification) {
        for (const auto& dependency : modification.requiredModificationIds()) {
            auto it = std::find(appliedModifications.begin(), appliedModifications.end(), dependency);
            if (it == appliedModifications.end()) {
                throw std::runtime_error(strenc("Required modification was not applied"));
            }
        }

        modifiedBinary = modification.apply(modifiedBinary);
        appliedModifications.push_back(modification.id());
    }
    
    return CBinary { modifiedBinary };
}

std::shared_ptr<IFormat> CBinaryFile::modifiedBinaryAsFormat() const
{
    const auto& fmt = format();
    if (fmt == Format::Windows_PE) {
        return std::make_shared<format::pe::CPeFormat>(modifiedBinary());
    } else {
        throw RuntimeException(strenc("Unsupported format"));
    }
}

Format CBinaryFile::format() const
{
    return m_attributes.format;
}

Architecture CBinaryFile::arch() const
{
    return m_attributes.arch;
}

BinaryFileAttributes_t CBinaryFile::attributes() const
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
    if (flags == BinaryFileFlags::NONE && m_flags > 0) {
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

bool CBinaryFile::hasModification(const CUuid& modificationId) const
{
    for (const auto& modification : m_vecBinaryModification) {
        if (modification.id() == modificationId) {
            return true;
        }
    }

    return false;
}

std::shared_ptr<const CBinaryModification> CBinaryFile::modification(const CUuid& modificationId) const
{
    for (const auto& modification : m_vecBinaryModification) {
        if (modification.id() == modificationId) {
            return std::make_shared<const CBinaryModification>(modification);
        }
    }

    return nullptr;
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

    const auto totalSizeDiff = modification.totalSizeDiff();
    if (totalSizeDiff != 0) {
        m_eventBus->publish(
            std::make_shared<program::core::modification::resize::CBinarySizeChangedEvent>(
                fileId(),
                modification.id(),
                modification.firstByteAddress(),
                totalSizeDiff
            )
        );
    }
}

