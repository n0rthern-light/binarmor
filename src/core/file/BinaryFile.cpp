#include "BinaryFile.hpp"
#include "core/file/BinaryAttributes.hpp"

CBinaryFile::CBinaryFile(const std::string& filePath, const CBinary& binary): m_filePath(filePath), m_binary(binary)
{
	m_attributes = BinaryAttributes_t();
	m_flags = 0;
	m_format = Format::UNKNOWN;
}

std::filesystem::path CBinaryFile::filePath() const
{
	return m_filePath;
}

std::string CBinaryFile::fileName() const
{
    return m_filePath.filename().string();
}

CBinary CBinaryFile::binary() const
{
	return m_binary;
}

bool CBinaryFile::hasFormatRecognized() const
{
	return m_format != Format::UNKNOWN;
}

void CBinaryFile::recognizeFormat(const Format& format)
{
	m_format = format;
}

Format CBinaryFile::format() const
{
    return m_format;
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
    return hasFlags(BinaryFileFlags::Analyzed) && hasFlags(BinaryFileFlags::Protected);
}

void CBinaryFile::assignAttributes(const BinaryAttributes_t& attributes)
{
	m_attributes = attributes;
}

void CBinaryFile::completeAnalysis()
{
	enableFlags(BinaryFileFlags::Analyzed);
}

