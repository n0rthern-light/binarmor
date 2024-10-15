#include "KeystoneAssembler.hpp"
#include "../defines.hpp"
#include "core/shared/attributes.hpp"
#include <cstring>
#include <shared/self_obfuscation/strenc.hpp>
#include <keystone/keystone.h>

using namespace program::core::assembler::keystone;
using namespace program::core::assembler;
using namespace program::core::shared;

CKeystoneAssembler::CKeystoneAssembler(Architecture architecture, Endianness endianness): m_architecture(architecture), m_endianness(endianness) { }

asm_opcodes CKeystoneAssembler::assemble(const asm_instructions& input)
{
    asm_opcodes opcodes;

    ks_engine *ks;
    ks_err err;

    switch (m_architecture) {
        case Architecture::X86:
            err = ks_open(KS_ARCH_X86, KS_MODE_32, &ks);
            break;
        case Architecture::X86_64:
            err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
            break;
        case Architecture::ARM64:
            err = ks_open(KS_ARCH_ARM64, KS_MODE_LITTLE_ENDIAN, &ks);
            break;
        default:
            throw std::invalid_argument(strenc("Unsupported architecture"));
            break;
    }
    if (err != KS_ERR_OK) {
        throw std::runtime_error(strenc("Failed to initialize Keystone engine"));
    }

    for (const std::string& line : input) {
        unsigned char *encode;
        size_t size, count;

        if (ks_asm(ks, line.c_str(), 0, &encode, &size, &count) != KS_ERR_OK) {
            ks_close(ks);
            throw std::runtime_error(strenc("Keystone assembly failed for: ") + line);
        }

        opcodes.insert(opcodes.end(), encode, encode + size);

        ks_free(encode);
    }
    ks_close(ks);

    return opcodes;
 }

