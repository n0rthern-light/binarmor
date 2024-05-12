#pragma once

enum class Format
{
	UNKNOWN = 0,
	Windows_PE = 1,
	Linux_ELF = 2,
	MacOS_MachO = 3,
};

enum class Architecture
{
	UNKNOWN = 0,
	X86 = 1,
	X86_64 = 2,
	ARM = 3,
	ARM64 = 4,
};

enum class Type
{
	UNKNOWN = 0,
	Executable = 1,
	Dynamic_Library = 2,
};
