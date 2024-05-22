#pragma once

#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/file/Binary.hpp>
#include <core/file/format/pe/PeFormat.hpp>

class BinaryMother
{
public:
	static CfstreamFileReader* fileReader()
	{
		static CfstreamFileReader* fr = new CfstreamFileReader();

		return fr;
	}

	static CPeFormat* readPeFromDisk(const char* path)
	{
		return new CPeFormat(new CBinary(fileReader()->read(path)));
	}

	static CPeFormat* x86exe()
	{
		static auto binary = readPeFromDisk("./binaries/windows/x86.exe");

		return binary;
	}

	static CPeFormat* x86dll()
	{
		static auto binary = readPeFromDisk("./binaries/windows/x86.dll");

		return binary;
	}

	static CPeFormat* x86_64exe()
	{
		static auto binary = readPeFromDisk("./binaries/windows/x86_64.exe");

		return binary;
	}

	static CPeFormat* x86_64dll()
	{
		static auto binary = readPeFromDisk("./binaries/windows/x86_64.dll");

		return binary;
	}
};

