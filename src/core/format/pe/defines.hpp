#ifndef CORE_FORMAT_PE_DEFINES_HPP_
#define CORE_FORMAT_PE_DEFINES_HPP_

#include <shared/types/defines.hpp>

constexpr unsigned char PE_SECTION_NULL_BYTE = 0x00;

constexpr uint_16 IMAGE_DOS_SIGNATURE = 0x5A4D;
constexpr uint_32 IMAGE_NT_SIGNATURE = 0x00004550;

constexpr uint_16 IMAGE_FILE_DLL = 0x2000;
constexpr uint_16 IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002;

constexpr uint_16 IMAGE_FILE_MACHINE_I386 = 0x014C;
constexpr uint_16 IMAGE_FILE_MACHINE_AMD64 = 0x8664;
constexpr uint_16 IMAGE_FILE_MACHINE_ARM = 0x01C0;
constexpr uint_16 IMAGE_FILE_MACHINE_ARM64 = 0xAA64;

constexpr uint_32 IMAGE_ORDINAL_FLAG32 = 0x80000000;
constexpr uint_64 IMAGE_ORDINAL_FLAG64 = 0x8000000000000000;

constexpr uint_8 IMAGE_DIRECTORY_ENTRY_IMPORT = 1;

constexpr uint_8 IMAGE_SIZEOF_SHORT_NAME = 8;

constexpr uint_32 IMAGE_SCN_TYPE_NO_PAD = 0x00000008;
constexpr uint_32 IMAGE_SCN_CNT_CODE = 0x00000020;
constexpr uint_32 IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040;
constexpr uint_32 IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080;
constexpr uint_32 IMAGE_SCN_LNK_OTHER = 0x00000100;
constexpr uint_32 IMAGE_SCN_LNK_INFO = 0x00000200;
constexpr uint_32 IMAGE_SCN_LNK_REMOVE = 0x00000800;
constexpr uint_32 IMAGE_SCN_LNK_COMDAT = 0x00001000;
constexpr uint_32 IMAGE_SCN_NO_DEFER_SPEC_EXC = 0x00004000;
constexpr uint_32 IMAGE_SCN_GPREL = 0x00008000;
constexpr uint_32 IMAGE_SCN_MEM_PURGEABLE = 0x00020000;
constexpr uint_32 IMAGE_SCN_MEM_LOCKED = 0x00040000;
constexpr uint_32 IMAGE_SCN_MEM_PRELOAD = 0x00080000;
constexpr uint_32 IMAGE_SCN_ALIGN_1BYTES = 0x00100000;
constexpr uint_32 IMAGE_SCN_ALIGN_2BYTES = 0x00200000;
constexpr uint_32 IMAGE_SCN_ALIGN_4BYTES = 0x00300000;
constexpr uint_32 IMAGE_SCN_ALIGN_8BYTES = 0x00400000;
constexpr uint_32 IMAGE_SCN_ALIGN_16BYTES = 0x00500000;
constexpr uint_32 IMAGE_SCN_ALIGN_32BYTES = 0x00600000;
constexpr uint_32 IMAGE_SCN_ALIGN_64BYTES = 0x00700000;
constexpr uint_32 IMAGE_SCN_ALIGN_128BYTES = 0x00800000;
constexpr uint_32 IMAGE_SCN_ALIGN_256BYTES = 0x00900000;
constexpr uint_32 IMAGE_SCN_ALIGN_512BYTES = 0x00A00000;
constexpr uint_32 IMAGE_SCN_ALIGN_1024BYTES = 0x00B00000;
constexpr uint_32 IMAGE_SCN_ALIGN_2048BYTES = 0x00C00000;
constexpr uint_32 IMAGE_SCN_ALIGN_4096BYTES = 0x00D00000;
constexpr uint_32 IMAGE_SCN_ALIGN_8192BYTES = 0x00E00000;
constexpr uint_32 IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000;
constexpr uint_32 IMAGE_SCN_MEM_DISCARDABLE = 0x02000000;
constexpr uint_32 IMAGE_SCN_MEM_NOT_CACHED = 0x04000000;
constexpr uint_32 IMAGE_SCN_MEM_NOT_PAGED = 0x08000000;
constexpr uint_32 IMAGE_SCN_MEM_SHARED = 0x10000000;
constexpr uint_32 IMAGE_SCN_MEM_EXECUTE = 0x20000000;
constexpr uint_32 IMAGE_SCN_MEM_READ = 0x40000000;
constexpr uint_32 IMAGE_SCN_MEM_WRITE = 0x80000000;

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

#endif // CORE_FORMAT_PE_DEFINES_HPP_
