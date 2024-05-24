#pragma once

#include <cstdint> // For standard integer types

// PE File Signatures
constexpr uint16_t IMAGE_DOS_SIGNATURE = 0x5A4D;      // MZ
constexpr uint32_t IMAGE_NT_SIGNATURE = 0x00004550;   // PE00

// Characteristics
constexpr uint16_t IMAGE_FILE_DLL = 0x2000;
constexpr uint16_t IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002;

// Machine identifiers for COFF headers
constexpr uint16_t IMAGE_FILE_MACHINE_I386 = 0x014C;   // Intel 386 or later processors and compatible processors
constexpr uint16_t IMAGE_FILE_MACHINE_AMD64 = 0x8664;  // x64 (AMD64 or Intel EM64T)
constexpr uint16_t IMAGE_FILE_MACHINE_ARM = 0x01C0;    // ARM little endian
constexpr uint16_t IMAGE_FILE_MACHINE_ARM64 = 0xAA64;  // ARM64 little endian

#define IMAGE_DIRECTORY_ENTRY_IMPORT 1

// DOS Header (at the file's beginning)
struct IMAGE_DOS_HEADER {
    uint16_t e_magic;    // Magic number (MZ)
    uint16_t e_cblp;     // Bytes on last page of file
    uint16_t e_cp;       // Pages in file
    uint16_t e_crlc;     // Relocations
    uint16_t e_cparhdr;  // Size of header in paragraphs
    uint16_t e_minalloc; // Minimum extra paragraphs needed
    uint16_t e_maxalloc; // Maximum extra paragraphs needed
    uint16_t e_ss;       // Initial (relative) SS value
    uint16_t e_sp;       // Initial SP value
    uint16_t e_csum;     // Checksum
    uint16_t e_ip;       // Initial IP value
    uint16_t e_cs;       // Initial (relative) CS value
    uint16_t e_lfarlc;   // File address of relocation table
    uint16_t e_ovno;     // Overlay number
    uint16_t e_res[4];   // Reserved words
    uint16_t e_oemid;    // OEM identifier (for e_oeminfo)
    uint16_t e_oeminfo;  // OEM information; e_oemid specific
    uint16_t e_res2[10]; // Reserved words
    int32_t  e_lfanew;   // File address of new exe header
};

// COFF File Header (part of the PE header)
struct IMAGE_FILE_HEADER {
    uint16_t Machine;              // The architecture type
    uint16_t NumberOfSections;     // Number of sections
    uint32_t TimeDateStamp;        // Time and date stamp
    uint32_t PointerToSymbolTable; // File offset of the COFF symbol table
    uint32_t NumberOfSymbols;      // Number of symbols in the symbol table
    uint16_t SizeOfOptionalHeader; // Size of the optional header
    uint16_t Characteristics;      // Characteristics
};

// Optional Data Directories included in the optional headers
struct IMAGE_DATA_DIRECTORY {
    uint32_t VirtualAddress;
    uint32_t Size;
};

// Standard COFF Fields for PE32 (32-bit)
struct IMAGE_OPTIONAL_HEADER32 {
    // Standard fields
    uint16_t Magic;               // Not magic, but identifies as PE32 (0x10b)
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint; // Entry point function address
    uint32_t BaseOfCode;
    uint32_t BaseOfData;

    // Windows-specific fields
    uint32_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

// Standard COFF Fields for PE32+ (64-bit)
struct IMAGE_OPTIONAL_HEADER64 {
    uint16_t Magic;               // Magic number, 0x20b for PE32+
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint64_t ImageBase;           // 64-bit address for PE32+
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint64_t SizeOfStackReserve;  // 64-bit size
    uint64_t SizeOfStackCommit;   // 64-bit size
    uint64_t SizeOfHeapReserve;   // 64-bit size
    uint64_t SizeOfHeapCommit;    // 64-bit size
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

// PE Header located at e_lfanew in the DOS header
struct IMAGE_NT_HEADERS32 {
    uint32_t Signature;      // PE\0\0 or 50 45 00 00
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

// PE Header located at e_lfanew in the DOS header
struct IMAGE_NT_HEADERS64 {
    uint32_t Signature;      // PE\0\0 or 50 45 00 00
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

struct IMAGE_SECTION_HEADER {
    uint8_t Name[8];
    union {
        uint32_t PhysicalAddress;
        uint32_t VirtualSize;
    } Misc;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
};

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    union {
        uint32_t   Characteristics;            // 0 for terminating null import descriptor
        uint32_t   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    } DUMMYUNIONNAME;
    uint32_t   TimeDateStamp;                  // 0 if not bound,
    uint32_t   ForwarderChain;                 // -1 if no forwarders
    uint32_t   Name;                           // RVA to DLL name
    uint32_t   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;

