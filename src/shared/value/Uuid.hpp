#ifndef SHARED_VALUE__UUID_HPP_
#define SHARED_VALUE__UUID_HPP_

#include "shared/self_obfuscation/strenc.hpp"
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <regex>

class CUuid {
    std::array<unsigned char, 16> uuid;

    void generate() {
        if (RAND_bytes(uuid.data(), uuid.size()) != 1) {
            throw std::runtime_error(strenc("Failed to generate random bytes for UUID"));
        }

        uuid[6] = (uuid[6] & 0x0F) | 0x40;
        uuid[8] = (uuid[8] & 0x3F) | 0x80;
    }

    void fromString(const std::string& uuidStr) {
        size_t index = 0;
        for (size_t i = 0; i < uuidStr.size(); ++i) {
            if (uuidStr[i] == '-') {
                continue;
            }
            uint8_t value = std::stoi(uuidStr.substr(i, 2), nullptr, 16);
            uuid[index++] = value;
            ++i;
        }
    }

    void fromSeed(const std::string& seed) {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(seed.c_str()), seed.size(), hash);

        for (size_t i = 0; i < uuid.size(); ++i) {
            uuid[i] = hash[i];
        }

        uuid[6] = (uuid[6] & 0x0F) | 0x40;

        uuid[8] = (uuid[8] & 0x3F) | 0x80;
    }

public:
    CUuid() {
        generate();
        CUuid::assertValidUuid(toString());
    }

    CUuid(const std::string& uuidOrSeed) {
        if (CUuid::isValidUuid(uuidOrSeed)) {
            fromString(uuidOrSeed);
        } else {
            fromSeed(uuidOrSeed);
        }

        CUuid::assertValidUuid(toString());
    }

    static bool isValidUuid(const std::string& uuid) {
        const std::regex uuidRegex(strenc("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"));
        return std::regex_match(uuid, uuidRegex);
    }

    static void assertValidUuid(const std::string& uuid) {
        if (!CUuid::isValidUuid(uuid)) {
            throw std::invalid_argument(strenc("Invalid UUID format"));
        }
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (size_t i = 0; i < uuid.size(); ++i) {
            if (i == 4 || i == 6 || i == 8 || i == 10) {
                oss << '-';
            }
            oss << std::setw(2) << static_cast<int>(uuid[i]);
        }
        return oss.str();
    }

    bool operator ==(const CUuid other) const {
        return toString() == other.toString();
    }
};

#endif // SHARED_VALUE__UUID_HPP_
