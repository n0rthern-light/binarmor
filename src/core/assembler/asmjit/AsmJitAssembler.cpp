#include "AsmJitAssembler.hpp"
#include <asmjit/asmjit.h>
#include "../defines.hpp"
#include <cstring>
#include <shared/self_obfuscation/strenc.hpp>

using namespace asmjit;

asm_opcodes CAsmJitAssembler::assemble(Architecture arch, const asm_instructions& input)
{
    std::vector<unsigned char> opcodes { };

    Environment env;
    env.setArch(Arch::kX86);

    CodeHolder code;
    code.init(env);

    x86::Assembler a(&code);

    a.mov(asmjit::x86::eax, dword_ptr(asmjit::x86::esp, 4));
    a.mov(asmjit::x86::ecx, dword_ptr(asmjit::x86::esp, 8));
    a.mov(asmjit::x86::edx, dword_ptr(asmjit::x86::esp, 12));

    a.movups(asmjit::x86::xmm0, ptr(asmjit::x86::ecx));
    a.movups(asmjit::x86::xmm1, ptr(asmjit::x86::edx));
    a.addps(asmjit::x86::xmm0, asmjit::x86::xmm1);
    a.movups(ptr(asmjit::x86::eax), asmjit::x86::xmm0);
    a.ret();

    CodeBuffer& buffer = code.textSection()->buffer();

    for (size_t i = 0; i < buffer.size(); i++)
    {
        auto byte = reinterpret_cast<unsigned char>(buffer.data()[i]);
        opcodes.push_back(byte);
    }

    return opcodes;
 }

