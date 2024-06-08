#ifndef CORE_ATTRIBUTES_HPP_
#define CORE_ATTRIBUTES_HPP_

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
	UNIVERSAL = 5,
};

enum class Type
{
	UNKNOWN = 0,
	Executable = 1,
	Dynamic_Library = 2,
};

enum class Endianness
{
	UNKNOWN = 0,
	LITTLE = 1,
	BIG = 2,
};

#endif // CORE_ATTRIBUTES_HPP_
