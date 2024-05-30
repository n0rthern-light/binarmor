#pragma once

#include "../Binary.hpp"
#include "../attributes.hpp"
#include "BinaryAttributes.hpp"
#include "flags.hpp"
#include <shared/event/IEventBus.hpp>
#include <string>

class CBinaryFile
{
	const std::string _filePath;
	const CBinary _binary;
	Format _format;
	uint_32 _flags;
	BinaryAttributes_t _attributes;
public:
	CBinaryFile(const std::string& filePath, const CBinary& binary);
	std::string filePath() const;
	CBinary binary() const;
	bool hasFormatRecognized() const;
	void recognizeFormat(const Format& format);
    Format format() const;
	void enableFlags(BinaryFileFlags flags);
	void disableFlags(BinaryFileFlags flags);
	bool hasFlags(BinaryFileFlags flags) const;
	bool hasAnyFlags() const;
	void completeAnalysis(const BinaryAttributes_t& attributes);
};

