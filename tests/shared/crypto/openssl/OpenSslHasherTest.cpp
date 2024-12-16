#include <gtest/gtest.h>
#include <shared/crypto/openssl/OpenSslHasher.hpp>

using namespace program::shared::crypto::openssl;

TEST(OpenSslHasherTest, WillCreateAValidHash) {
    auto hasher = std::make_unique<COpenSslHasher>();

    ASSERT_STREQ(hasher->sha256FromString("aaa").c_str(), "9834876dcfb05cb167a5c24953eba58c4ac89b1adf57f28f2f9d09af107ee8f0");
    ASSERT_STREQ(hasher->sha256FromString("000").c_str(), "2ac9a6746aca543af8dff39894cfe8173afba21eb01c6fae33d52947222855ef");
    ASSERT_STREQ(hasher->sha256FromString("Better Call Saul is an awesome TV Series!").c_str(), "4b2d1abc7ad6f99ff2cd4b22f1312c6fee45fe10078f3f8d46b89be96e5282e2");

    ASSERT_STREQ(hasher->sha256FromBytes({'a', 'a', 'a'}).c_str(), "9834876dcfb05cb167a5c24953eba58c4ac89b1adf57f28f2f9d09af107ee8f0");
    ASSERT_STREQ(hasher->sha256FromBytes({'0', '0', '0'}).c_str(), "2ac9a6746aca543af8dff39894cfe8173afba21eb01c6fae33d52947222855ef");
}

