#include "PeImport.hpp"

CPeImport::CPeImport(
    const std::string& module,
    const std::string& name,
    const uint16_t& hint,
    const uint32_t& ordinal
) {
    _module = module;
    _name = name;
    _hint = hint;
    _ordinal = ordinal;
}

