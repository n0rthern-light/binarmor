#include "PeImport.hpp"
#include "core/file/BinaryPointer.hpp"
#include <shared/value/AddressType.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CPeImport::CPeImport(
    const std::string& name,
    const uint_16& hint,
    const uint_32& ordinal,
    const uint_32& rva,
    const uint_32& size,
    const CBinaryPointer& origin
): _name(name), _hint(hint), _ordinal(ordinal), _rva(rva), _size(size), _origin(origin)
{ }

