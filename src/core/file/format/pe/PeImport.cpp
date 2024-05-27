#include "PeImport.hpp"
#include <shared/value/AddressType.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CPeImport::CPeImport(
    const std::string& module,
    const std::string& name,
    const uint_16& hint,
    const uint_32& ordinal
) {
    _module = module;
    _name = name;
    _hint = hint;
    _ordinal = ordinal;
}

