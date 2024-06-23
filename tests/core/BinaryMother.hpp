#ifndef TESTS_CORE__BINARY_MOTHER_HPP_
#define TESTS_CORE__BINARY_MOTHER_HPP_

#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/shared/Binary.hpp>
#include <core/format/pe/PeFormat.hpp>

class BinaryMother
{
public:
    static CfstreamFileReader* fileReader()
    {
        static CfstreamFileReader* fr = new CfstreamFileReader();

        return fr;
    }

    static std::string testBinaryPath(const std::string relativeBinaryPath = "")
    {
        return std::string(_TEST_BINARIES_DIR) + relativeBinaryPath;
    }

    static CPeFormat* readPeFromDisk(const char* path)
    {
        return new CPeFormat(*(new CBinary(fileReader()->read(path))));
    }

    static CPeFormat* x86exe()
    {
        auto path = testBinaryPath("/windows/x86.exe");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static CPeFormat* x86dll()
    {
        auto path = testBinaryPath("/windows/x86.dll");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static CPeFormat* x86_64exe()
    {
        auto path = testBinaryPath("/windows/x86_64.exe");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }

    static CPeFormat* x86_64dll()
    {
        auto path = testBinaryPath("/windows/x86_64.dll");
        static auto binary = readPeFromDisk(path.c_str());

        return binary;
    }
};

#endif // TESTS_CORE__BINARY_MOTHER_HPP_
