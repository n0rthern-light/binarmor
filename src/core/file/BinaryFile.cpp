#include "BinaryFile.hpp"

CBinaryFile::CBinaryFile(const std::string& _filePath, const CBinary& _binary): filePath(_filePath), binary(_binary)
{
	attributes = BinaryAttributes_t();
	flags = 0;
	format = Format::UNKNOWN;
}

const std::string& CBinaryFile::getFilePath() const
{
	return filePath;
}

const CBinary& CBinaryFile::getBinary() const
{
	return binary;
}

bool CBinaryFile::hasFormatRecognized() const
{
	return format != Format::UNKNOWN;
}

void CBinaryFile::recognizeFormat(const Format& _format)
{
	format = _format;
}

void CBinaryFile::enableFlags(BinaryFileFlags _flags)
{
	flags |= static_cast<unsigned int>(_flags);
}

void CBinaryFile::disableFlags(BinaryFileFlags _flags)
{
	flags &= ~static_cast<unsigned int>(_flags);
}

bool CBinaryFile::hasFlags(BinaryFileFlags _flags) const
{
	return (flags & static_cast<uint32_t>(_flags)) == static_cast<uint32_t>(_flags);
}

void CBinaryFile::completeAnalysis(const BinaryAttributes_t& _attributes)
{
	attributes = _attributes;
	enableFlags(BinaryFileFlags::Analyzed);
}
