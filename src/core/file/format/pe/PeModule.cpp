#include "PeModule.hpp"

CPeModule::CPeModule(
    const std::string& name,
    const uint_32& rva,
    const uint_32& size,
    const CBinaryPointer& origin,
    const pe_import_vec& imports
): _name(name), _rva(rva), _size(size), _origin(origin), _imports(imports)
{ }

std::string CPeModule::name() const
{
    return _name;
}

uint_32 CPeModule::rva() const
{
    return _rva;
}

uint_32 CPeModule::size() const
{
    return _size;
}

CBinaryPointer CPeModule::origin() const
{
    return _origin;
}

pe_import_vec CPeModule::imports() const
{
    return _imports;
}

