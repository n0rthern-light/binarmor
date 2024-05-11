#pragma once

enum class Format
{
	UNKNOWN = 0,
	Windows_PE = 1,
	Linux_ELF = 2,
	MacOS_MachO = 3,
};

enum class Machine
{
	UNKNOWN = 0,
	X86 = 1,
	X86_64 = 2,
	ARM64 = 3,
};

enum class Characteristics
{
	UNKNOWN = 0,
	Executable = 1,
	Dynamic_Library = 2,
};

struct AnalysisResult_t
{
	Format format;
	Machine machine;
	Characteristics characterisitcs;

	AnalysisResult_t();
};
