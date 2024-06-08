#ifndef SRC_CORE_FORMAT_PE_DEFINES_HPP_
#define SRC_CORE_FORMAT_PE_DEFINES_HPP_





#include <shared/types/defines.hpp>

// PE File Signatures
constexpr uint_16 IMAGE_DOS_SIGNATURE = 0x5A4D;      // MZ
constexpr uint_32 IMAGE_NT_SIGNATURE = 0x00004550;   // PE00

// Characteristics
constexpr uint_16 IMAGE_FILE_DLL = 0x2000;
constexpr uint_16 IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002;

// Machine identifiers for COFF headers
constexpr uint_16 IMAGE_FILE_MACHINE_I386 = 0x014C;   // Intel 386 or later processors and compatible processors
constexpr uint_16 IMAGE_FILE_MACHINE_AMD64 = 0x8664;  // x64 (AMD64 or Intel EM64T)
constexpr uint_16 IMAGE_FILE_MACHINE_ARM = 0x01C0;    // ARM little endian
constexpr uint_16 IMAGE_FILE_MACHINE_ARM64 = 0xAA64;  // ARM64 little endian

constexpr uint_32 IMAGE_ORDINAL_FLAG32 = 0x80000000;
constexpr uint_64 IMAGE_ORDINAL_FLAG64 = 0x8000000000000000;

constexpr uint_8 IMAGE_DIRECTORY_ENTRY_IMPORT = 1;

// DOS Header (at the file's beginning)
struct IMAGE_DOS_HEADER {
    uint_16 e_magic;    // Magic number (MZ)
    uint_16 e_cblp;     // Bytes on last page of file
    uint_16 e_cp;       // Pages in file
    uint_16 e_crlc;     // Relocations
    uint_16 e_cparhdr;  // Size of header in paragraphs
    uint_16 e_minalloc; // Minimum extra paragraphs needed
    uint_16 e_maxalloc; // Maximum extra paragraphs needed
    uint_16 e_ss;       // Initial (relative) SS value
    uint_16 e_sp;       // Initial SP value
    uint_16 e_csum;     // Checksum
    uint_16 e_ip;       // Initial IP value
    uint_16 e_cs;       // Initial (relative) CS value
    uint_16 e_lfarlc;   // File address of relocation table
    uint_16 e_ovno;     // Overlay number
    uint_16 e_res[4];   // Reserved words
    uint_16 e_oemid;    // OEM identifier (for e_oeminfo)
    uint_16 e_oeminfo;  // OEM information; e_oemid specific
    uint_16 e_res2[10]; // Reserved words
    uint_32 e_lfanew;   // File address of new exe header
};

// COFF File Header (part of the PE header)
struct IMAGE_FILE_HEADER {
    uint_16 Machine;              // The architecture type
    uint_16 NumberOfSections;     // Number of sections
    uint_32 TimeDateStamp;        // Time and date stamp
    uint_32 PointerToSymbolTable; // File offset of the COFF symbol table
    uint_32 NumberOfSymbols;      // Number of symbols in the symbol table
    uint_16 SizeOfOptionalHeader; // Size of the optional header
    uint_16 Characteristics;      // Characteristics
};

// Optional Data Directories included in the optional headers
struct IMAGE_DATA_DIRECTORY {
    uint_32 VirtualAddress;
    uint_32 Size;
};

// Standard COFF Fields for PE32 (32-bit)
struct IMAGE_OPTIONAL_HEADER32 {
    // Standard fields
    uint_16 Magic;               // Not magic, but identifies as PE32 (0x10b)
    uint_8  MajorLinkerVersion;
    uint_8  MinorLinkerVersion;
    uint_32 SizeOfCode;
    uint_32 SizeOfInitializedData;
    uint_32 SizeOfUninitializedData;
    uint_32 AddressOfEntryPoint; // Entry point function address
    uint_32 BaseOfCode;
    uint_32 BaseOfData;

    // Windows-specific fields
    uint_32 ImageBase;
    uint_32 SectionAlignment;
    uint_32 FileAlignment;
    uint_16 MajorOperatingSystemVersion;
    uint_16 MinorOperatingSystemVersion;
    uint_16 MajorImageVersion;
    uint_16 MinorImageVersion;
    uint_16 MajorSubsystemVersion;
    uint_16 MinorSubsystemVersion;
    uint_32 Win32VersionValue;
    uint_32 SizeOfImage;
    uint_32 SizeOfHeaders;
    uint_32 CheckSum;
    uint_16 Subsystem;
    uint_16 DllCharacteristics;
    uint_32 SizeOfStackReserve;
    uint_32 SizeOfStackCommit;
    uint_32 SizeOfHeapReserve;
    uint_32 SizeOfHeapCommit;
    uint_32 LoaderFlags;
    uint_32 NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

// Standard COFF Fields for PE32+ (64-bit)
struct IMAGE_OPTIONAL_HEADER64 {
    uint_16 Magic;               // Magic number, 0x20b for PE32+
    uint_8  MajorLinkerVersion;
    uint_8  MinorLinkerVersion;
    uint_32 SizeOfCode;
    uint_32 SizeOfInitializedData;
    uint_32 SizeOfUninitializedData;
    uint_32 AddressOfEntryPoint;
    uint_32 BaseOfCode;
    uint_64 ImageBase;           // 64-bit address for PE32+
    uint_32 SectionAlignment;
    uint_32 FileAlignment;
    uint_16 MajorOperatingSystemVersion;
    uint_16 MinorOperatingSystemVersion;
    uint_16 MajorImageVersion;
    uint_16 MinorImageVersion;
    uint_16 MajorSubsystemVersion;
    uint_16 MinorSubsystemVersion;
    uint_32 Win32VersionValue;
    uint_32 SizeOfImage;
    uint_32 SizeOfHeaders;
    uint_32 CheckSum;
    uint_16 Subsystem;
    uint_16 DllCharacteristics;
    uint_64 SizeOfStackReserve;  // 64-bit size
    uint_64 SizeOfStackCommit;   // 64-bit size
    uint_64 SizeOfHeapReserve;   // 64-bit size
    uint_64 SizeOfHeapCommit;    // 64-bit size
    uint_32 LoaderFlags;
    uint_32 NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

// PE Header located at e_lfanew in the DOS header
struct IMAGE_NT_HEADERS32 {
    uint_32 Signature;      // PE\0\0 or 50 45 00 00
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

// PE Header located at e_lfanew in the DOS header
struct IMAGE_NT_HEADERS64 {
    uint_32 Signature;      // PE\0\0 or 50 45 00 00
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

struct IMAGE_SECTION_HEADER {
    uint_8 Name[8];
    union {
        uint_32 PhysicalAddress;
        uint_32 VirtualSize;
    } Misc;
    uint_32 VirtualAddress;
    uint_32 SizeOfRawData;
    uint_32 PointerToRawData;
    uint_32 PointerToRelocations;
    uint_32 PointerToLinenumbers;
    uint_16 NumberOfRelocations;
    uint_16 NumberOfLinenumbers;
    uint_32 Characteristics;
};

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    uint_32   OriginalFirstThunk;            // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    uint_32   TimeDateStamp;                  // 0 if not bound,
    uint_32   ForwarderChain;                 // -1 if no forwarders
    uint_32   Name;                           // RVA to DLL name
    uint_32   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_IMPORT_BY_NAME {
    uint_16 Hint;
    char Name[1]; // Flexible array member, actual size varies
} IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;

typedef struct _IMAGE_THUNK_DATA64 {
    union {
        uint_64 ForwarderString;
        uint_64 Function;
        uint_64 Ordinal;
        uint_64 AddressOfData;
    } u1;
} IMAGE_THUNK_DATA64, *PIMAGE_THUNK_DATA64;

typedef struct _IMAGE_THUNK_DATA32 {
    union {
        uint_32 ForwarderString;
        uint_32 Function;
        uint_32 Ordinal;
        uint_32 AddressOfData;
    } u1;
} IMAGE_THUNK_DATA32, *PIMAGE_THUNK_DATA32;




#endif // SRC_CORE_FORMAT_PE_DEFINES_HPP_
