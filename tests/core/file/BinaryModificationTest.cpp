#include "core/file/BinaryModification.hpp"
#include <gtest/gtest.h>
#include "core/modification/diff/DiffExtractor.hpp"
#include "shared/crypto/openssl/OpenSslHasher.hpp"
#include "shared/diff/diff_match_patch.hpp"
#include "../BinaryMother.hpp"
#include <vector>
#include <stdio.h>

const auto x86exe = BinaryMother::x86exe();
const auto x86_64dll = BinaryMother::x86_64dll();
const auto hasher = new COpenSslHasher();

TEST(BinaryModificationTest, CanModifyFullExecutablesUsingDomainDiff)
{
    // given
    const auto source = x86exe->binary()->bytes();
    const auto target = x86_64dll->binary()->bytes();

    // when
    const auto diff = CDiffExtractor::extract(source, target);

    const auto modification = CBinaryModification {
        CUuid { "BINARY_TRANSLATION" },
        BinaryModificationType::APPEND_CODE,
        diff,
        { }
    };

    const auto modified = modification.apply(source);

    // then
    ASSERT_EQ(modified.size(), target.size());

    const auto sourceHash = hasher->sha256FromBytes(source); const auto targetHash = hasher->sha256FromBytes(target);
    const auto modifiedHash = hasher->sha256FromBytes(modified);
    ASSERT_STREQ(modifiedHash.c_str(), targetHash.c_str());
}

TEST(BinaryModificationTest, CanModifyWhenSourceIsBiggerThanTarget)
{
    // given
    const auto source = x86exe->binary()->part(0, 3241).bytes();
    const auto target = x86_64dll->binary()->part(963, 723).bytes();

    // when
    const auto diff = CDiffExtractor::extract(source, target);

    const auto modification = CBinaryModification {
        CUuid { "BINARY_TRANSLATION" },
        BinaryModificationType::APPEND_CODE,
        diff,
        { }
    };

    const auto modified = modification.apply(source);

    // then
    ASSERT_EQ(modified.size(), target.size());

    const auto sourceHash = hasher->sha256FromBytes(source); const auto targetHash = hasher->sha256FromBytes(target);
    const auto modifiedHash = hasher->sha256FromBytes(modified);
    ASSERT_STREQ(modifiedHash.c_str(), targetHash.c_str());
}

TEST(BinaryModificationTest, CanModifyWhenSourceIsSmallerThanTarget)
{
    // given
    const auto source = x86exe->binary()->part(1432, 583).bytes();
    const auto target = x86_64dll->binary()->part(958, 4321).bytes();

    // when
    const auto diff = CDiffExtractor::extract(source, target);

    const auto modification = CBinaryModification {
        CUuid { "BINARY_TRANSLATION" },
        BinaryModificationType::APPEND_CODE,
        diff,
        { }
    };

    const auto modified = modification.apply(source);

    // then
    ASSERT_EQ(modified.size(), target.size());

    const auto sourceHash = hasher->sha256FromBytes(source); const auto targetHash = hasher->sha256FromBytes(target);
    const auto modifiedHash = hasher->sha256FromBytes(modified);
    ASSERT_STREQ(modifiedHash.c_str(), targetHash.c_str());
}

TEST(BinaryModificationTest, CanModifyUsingDiffAlgorithmDirectly)
{
    // given
    const auto source = x86exe->binary()->part(0, 250).bytes();
    const auto target = x86_64dll->binary()->part(1000, 250).bytes();

    // when
    const auto diff = diff::match(source, target);
    const auto modified = diff::patch(source, diff);

    // then
    ASSERT_EQ(modified.size(), target.size());
    const auto modifiedHash = hasher->sha256FromBytes(modified);
    const auto targetHash = hasher->sha256FromBytes(target);
    ASSERT_STREQ(modifiedHash.c_str(), targetHash.c_str());
}

