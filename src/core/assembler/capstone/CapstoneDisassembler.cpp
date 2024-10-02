#include "CapstoneDisassembler.hpp"
#include "../defines.hpp"
#include "core/shared/attributes.hpp"
#include <cstring>
#include <shared/self_obfuscation/strenc.hpp>
#include <capstone/capstone.h>

CCapstoneDisassembler::CCapstoneDisassembler(Architecture architecture, Endianness endianness): m_architecture(architecture), m_endianness(endianness) { }

asm_instructions CCapstoneDisassembler::disassemble(const asm_opcodes& input)
{
    asm_instructions instructions;
    csh handle;
    cs_insn *insn;
    size_t count;

    cs_mode mode = CS_MODE_LITTLE_ENDIAN;

    switch (m_architecture) {
        case Architecture::X86:
            if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK)
                throw std::runtime_error("Failed to initialize Capstone for x86");
            break;
        case Architecture::X86_64:
            if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
                throw std::runtime_error("Failed to initialize Capstone for x86_64");
            break;
        case Architecture::ARM64:
            mode = (m_endianness == Endianness::LITTLE) ? CS_MODE_LITTLE_ENDIAN : CS_MODE_BIG_ENDIAN;
            if (cs_open(CS_ARCH_AARCH64, mode, &handle) != CS_ERR_OK)
                throw std::runtime_error("Failed to initialize Capstone for ARM64");
            break;
        default:
            throw std::invalid_argument("Unsupported architecture");
    }

    cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

    count = cs_disasm(handle, input.data(), input.size(), 0x1000, 0, &insn);
    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            std::string instruction;
            if (strcmp(insn[i].op_str, "") != 0) {
                instruction = std::string(insn[i].mnemonic) + " " + insn[i].op_str;
            } else {
                instruction = std::string(insn[i].mnemonic);
            }

            instructions.push_back(instruction);
        }
        cs_free(insn, count);
    } else {
        cs_close(&handle);
        throw std::runtime_error("Failed to disassemble the provided code.");
    }

    cs_close(&handle);

    return instructions;
 }

