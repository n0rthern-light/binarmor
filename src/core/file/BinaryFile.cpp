#include "BinaryFile.hpp"

CBinaryFile::CBinaryFile(const std::string& _filePath, const CBinary& _binary): filePath(_filePath), binary(_binary)
{
	analysis = AnalysisResult_t();
	flags = 0;
}

const CBinary& CBinaryFile::getBinary() const
{
	return binary;
}

const std::string& CBinaryFile::getFilePath() const
{
	return filePath;
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

void CBinaryFile::applyAnalysis(const AnalysisResult_t& result)
{
	analysis = result;
	enableFlags(BinaryFileFlags::Analyzed);
}
