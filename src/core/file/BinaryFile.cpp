#include "BinaryFile.hpp"

CBinaryFile::CBinaryFile(const std::string& filePath, const CBinary& binary): _filePath(filePath), _binary(binary)
{
	_attributes = BinaryAttributes_t();
	_flags = 0;
	_format = Format::UNKNOWN;
}

std::string CBinaryFile::filePath() const
{
	return _filePath;
}

CBinary CBinaryFile::binary() const
{
	return _binary;
}

bool CBinaryFile::hasFormatRecognized() const
{
	return _format != Format::UNKNOWN;
}

void CBinaryFile::recognizeFormat(const Format& format)
{
	_format = format;
}

void CBinaryFile::enableFlags(BinaryFileFlags flags)
{
	_flags |= static_cast<uint_32>(flags);
}

void CBinaryFile::disableFlags(BinaryFileFlags flags)
{
	_flags &= ~static_cast<uint_32>(flags);
}

bool CBinaryFile::hasFlags(BinaryFileFlags flags) const
{
    if (flags == BinaryFileFlags::None && _flags > 0) {
        return false;
    }

	return (_flags & static_cast<uint_32>(flags)) == static_cast<uint_32>(flags);
}

bool CBinaryFile::hasAnyFlags() const
{
    return _flags > 0;
}

void CBinaryFile::completeAnalysis(const BinaryAttributes_t& attributes)
{
	_attributes = attributes;
	enableFlags(BinaryFileFlags::Analyzed);
}

