#include "BinaryFile.hpp"
#include "core/file/BinaryAttributes.hpp"

CBinaryFile::CBinaryFile(const std::string& filePath, const CBinary& binary, uint_32 flags, const BinaryAttributes_t& attributes): m_filePath(filePath), m_binary(binary), m_flags(flags), m_attributes(attributes)
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

CBinary CBinaryFile::binary() const
{
	return m_binary;
}

Format CBinaryFile::format() const
{
    return m_attributes.format;
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

void CBinaryFile::assignAttributes(const BinaryAttributes_t& attributes)
{
	m_attributes = attributes;
}

