#include <gtest/gtest.h>
#include <shared/crypto/openssl/OpenSslCrypter.hpp>
#include <tuple>

using namespace program::shared::types;
using namespace program::shared::crypto::openssl;

class OpenSslCrypterStringTest : public ::testing::TestWithParam<std::tuple<std::string, std::string>> { };
class OpenSslCrypterByteTest : public ::testing::TestWithParam<std::tuple<byte_vec, std::string>> { };

double calculateEntropy(const byte_vec& data) {
    std::array<int, 256> frequencies = {0};

    for (unsigned char byte : data) {
        frequencies[byte]++;
    }

    double entropy = 0.0;
    size_t dataSize = data.size();
    for (int freq : frequencies) {
        if (freq > 0) {
            double probability = static_cast<double>(freq) / dataSize;
            entropy -= probability * log2(probability);
        }
    }

    return entropy;
}

TEST_P(OpenSslCrypterStringTest, WillEncryptAndDecryptStringCorrectly) {
    auto crypter = std::make_unique<COpenSslCrypter>();

    const std::string original = std::get<0>(GetParam());
    const std::string key = std::get<1>(GetParam());

    const auto xored = crypter->xorString(original, key);
    ASSERT_NE(xored.c_str(), original.c_str());
    ASSERT_EQ(xored.size(), original.size());

    const auto unxored = crypter->xorString(xored, key);
    ASSERT_STREQ(unxored.c_str(), original.c_str());
}

TEST_P(OpenSslCrypterByteTest, WillEncryptAndDecryptBytesCorrectly) {
    auto crypter = std::make_unique<COpenSslCrypter>();

    const byte_vec original = std::get<0>(GetParam());
    const std::string key = std::get<1>(GetParam());

    const auto xored = crypter->xorBytes(original, key);
    ASSERT_NE(xored, original);
    ASSERT_EQ(xored.size(), original.size());

    const auto unxored = crypter->xorBytes(xored, key);
    ASSERT_EQ(unxored, original);
}

TEST_P(OpenSslCrypterStringTest, XoredEntropyWillBeGreater) {
    auto crypter = std::make_unique<COpenSslCrypter>();

    const std::string original = std::get<0>(GetParam());
    if (original == "" || original == " " || original == "!@#$%^&*()") { 
        // entropy will be always equal in this case
        return;
    }
    const std::string key = std::get<1>(GetParam());

    const auto xored = crypter->xorString(original, key);
    const auto xoredEntropy = calculateEntropy(byte_vec(xored.begin(), xored.end()));
    const auto originalEntropy = calculateEntropy(byte_vec(original.begin(), original.end()));

    ASSERT_GT(xoredEntropy, originalEntropy);
}

TEST_P(OpenSslCrypterByteTest, XoredEntropyWillBeGreater) {
    auto crypter = std::make_unique<COpenSslCrypter>();

    const byte_vec original = std::get<0>(GetParam());
    const std::string key = std::get<1>(GetParam());

    const auto xored = crypter->xorBytes(original, key);
    const auto xoredEntropy = calculateEntropy(xored);
    const auto originalEntropy = calculateEntropy(original);

    ASSERT_GT(xoredEntropy, originalEntropy);
}

INSTANTIATE_TEST_SUITE_P(
    OpenSslCrypterStringTestMulti,
    OpenSslCrypterStringTest,
    ::testing::Values(
        std::make_tuple("Hello, World!", "my_secret_key"),
        std::make_tuple("", "key"),
        std::make_tuple(" ", "key"),
        std::make_tuple("!@#$%^&*()", "key"),
        std::make_tuple("Very long string for testing purposes", "shortkey"),
        std::make_tuple("Unicode: ??", "key"),
        std::make_tuple("Another string with more content", "another_key_1234"),
        std::make_tuple(std::string(1024, 'A'), "longkey12345678"),
        std::make_tuple(std::string(2048, 'B'), "key_for_testing"),
        std::make_tuple(std::string(512, 'C') + "SOME_EXTRA_TEXT", "key"),
        std::make_tuple(std::string(1000, 'D'), "key_key_key_key"),
        std::make_tuple("Test string with digits 1234567890", "key123"),
        std::make_tuple("Mixed case STRING with Spec!@# characters", "C@mKey"),
        std::make_tuple("Repetitive: ababababababababababababababababab", "repeatkey"),
        std::make_tuple("This is a very very very very long string to test the encryption and decryption process", "longkey")
    )
);

byte_vec concatenate(const byte_vec& first) {
    return first; 
}

template <typename... Args>
byte_vec concatenate(const byte_vec& first, const Args&... args) {
    byte_vec result = first;
    (result.insert(result.end(), args.begin(), args.end()), ...);
    return result;
}

INSTANTIATE_TEST_SUITE_P(
    OpenSslCrypterByteTestMulti,
    OpenSslCrypterByteTest,
    ::testing::Values(
        std::make_tuple(concatenate(byte_vec(512, 0x01), byte_vec(512, 0xFF)), "1c1eb614-fa5b-4ee6-a40a-54465ba5b617"),
        std::make_tuple(concatenate(byte_vec(256, 0xAA), byte_vec(256, 0x55), byte_vec(256, 0x00)), "5358ceae-b122-40a4-bd49-6db57bdf98e5"),
        std::make_tuple(concatenate(byte_vec(100, 0xAB), byte_vec(150, 0xCD), byte_vec(250, 0xEF)), "2fcefb0d-b40b-46e8-b5f3-31063383eaf8"),
        std::make_tuple(concatenate(byte_vec(1024, 0x00)), "779086ba-3285-4110-bfdc-42c1cbc00dbd"),
        std::make_tuple(concatenate(byte_vec{0xDE, 0xAD}, byte_vec{0xBE, 0xBE}, byte_vec{0xCA, 0xFE, 0xBE, 0xBE}), "65183e85-671b-4cf7-a9e3-b9c7d1014e86"),
        std::make_tuple(concatenate(byte_vec{0x12, 0x34}, byte_vec{0x56, 0x56}, byte_vec{0x9A, 0xBC, 0x56, 0xF0}), "1088b953-3b86-4ad8-a846-6fc795bc9005"),
        std::make_tuple(concatenate(byte_vec(1000, 0x11), byte_vec(1000, 0x22)), "e80dd725-4d70-49f3-800a-d04b32949528")
    )
);
