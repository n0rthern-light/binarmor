#include "core/file/BinaryModification.hpp"
#include <gtest/gtest.h>
#include "core/modification/diff/DiffExtractor.hpp"
#include "shared/crypto/openssl/OpenSslHasher.hpp"
#include "shared/value/Unsigned.hpp"
#include "../BinaryMother.hpp"
#include <vector>
#include <stdio.h>

const auto x86exe = BinaryMother::x86exe();
const auto x86_64dll = BinaryMother::x86_64dll();
const auto hasher = new COpenSslHasher();

TEST(BinaryModificationTest, CanModifyUsingDiff)
{
    const auto source = x86exe->binary()->bytes();

    const auto target = x86_64dll->binary()->bytes();
    const auto targetHash = hasher->sha256FromBytes(target);

    const auto diff = CDiffExtractor::extract(source, target);

    //ASSERT_EQ(diff.size(), 647);

    const auto modification = CBinaryModification {
        CUuid { "BINARY_TRANSLATION" },
        BinaryModificationType::APPEND_CODE,
        diff,
        { }
    };

    const auto modified = modification.apply(source);
    const auto modifiedHash = hasher->sha256FromBytes(modified);

    ASSERT_EQ(modified.size(), target.size());
    //ASSERT_STREQ(modifiedHash.c_str(), targetHash.c_str());

    //const auto outputDiff = CDiffExtractor::extract(target, modified);
    //ASSERT_EQ(outputDiff.size(), 0);
}

