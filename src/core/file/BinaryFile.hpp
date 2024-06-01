#pragma once

#include "../Binary.hpp"
#include "../attributes.hpp"
#include "BinaryAttributes.hpp"
#include "flags.hpp"
#include <string>
#include <filesystem>

class CBinaryFile
{
	const std::filesystem::path m_filePath;
	const CBinary m_binary;
	Format m_format;
	uint_32 m_flags;
	BinaryAttributes_t m_attributes;
public:
	CBinaryFile(const std::string& filePath, const CBinary& binary);
    std::filesystem::path filePath() const;
    std::string fileName() const;
	CBinary binary() const;
	bool hasFormatRecognized() const;
	void recognizeFormat(const Format& format);
    Format format() const;
    BinaryAttributes_t attributes() const;
	void enableFlags(BinaryFileFlags flags);
	void disableFlags(BinaryFileFlags flags);
	bool hasFlags(BinaryFileFlags flags) const;
	bool hasAnyFlags() const;
    bool isProtectedByBinarmor() const;
    void assignAttributes(const BinaryAttributes_t& attributes);
	void completeAnalysis();
};

