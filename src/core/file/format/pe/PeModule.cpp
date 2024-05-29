#include "PeModule.hpp"

CPeModule::CPeModule(
    const std::string& name,
    const uint_32& rvaImportDescriptor,
    const uint_32& sizeOfImportDescriptor,
    const pe_import_vec& imports
): _name(name), _rvaImportDescriptor(rvaImportDescriptor), _sizeOfImportDescriptor(sizeOfImportDescriptor), _imports(imports)
{ }

std::string CPeModule::name() const
{
    return _name;
}

uint_32 CPeModule::rvaImportDescriptor() const
{
    return _rvaImportDescriptor;
}

uint_32 CPeModule::sizeOfImportDescriptor() const
{
    return _sizeOfImportDescriptor;
}

pe_import_vec CPeModule::imports() const
{
    return _imports;
}

