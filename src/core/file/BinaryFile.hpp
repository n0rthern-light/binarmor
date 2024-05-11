#pragma once
#include "Binary.hpp"
#include "BinaryFileFlags.hpp"
#include <string>

class CBinaryFile
{
	const std::string filePath;
	const CBinary binary;
	unsigned int flags;
public:
	CBinaryFile(const std::string& _filePath, const CBinary& _binary);
	const CBinary& getBinary() const;
	const std::string& getFilePath() const;
	void enableFlags(BinaryFileFlags _flags);
	void disableFlags(BinaryFileFlags _flags);
	bool hasFlags(BinaryFileFlags _flags) const;
};
