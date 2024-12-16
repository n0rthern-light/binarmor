#ifndef TESTS_CORE__BINARY_MOTHER_HPP_
#define TESTS_CORE__BINARY_MOTHER_HPP_

#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/shared/Binary.hpp>
#include <core/format/pe/PeFormat.hpp>

class BinaryMother
{
public:
    static program::core::file::fstream::CfstreamFileSystem* fileReader()
    {
        static program::core::file::fstream::CfstreamFileSystem* fr = new program::core::file::fstream::CfstreamFileSystem();

        return fr;
    }

    static std::string testBinaryPath(const std::string relativeBinaryPath = "")
    {
        return std::string(_TEST_BINARIES_DIR) + relativeBinaryPath;
    }

    static program::core::format::pe::CPeFormat* readPeFromDisk(const char* path)
    {
        return new program::core::format::pe::CPeFormat(*(new program::core::shared::CBinary(fileReader()->read(path))));
    }

    static program::core::format::pe::CPeFormat* x86exe()
    {
        auto path = testBinaryPath("/windows/x86.exe");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static program::core::format::pe::CPeFormat* metin2exe()
    {
        auto path = testBinaryPath("/windows/metin2clientVMPDumpFixedTotalDisabledTls.exe");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static program::core::format::pe::CPeFormat* x86dll()
    {
        auto path = testBinaryPath("/windows/x86.dll");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static program::core::format::pe::CPeFormat* x86_64exe()
    {
        auto path = testBinaryPath("/windows/x86_64.exe");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static program::core::format::pe::CPeFormat* x86_64dll()
    {
        auto path = testBinaryPath("/windows/x86_64.dll");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }
};

#endif // TESTS_CORE__BINARY_MOTHER_HPP_
