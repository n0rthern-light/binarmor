#include "PeModule.hpp"
#include "core/format/pe/PeImport.hpp"
#include <memory>

CPeModule::CPeModule(
    const std::string& name,
    const uint_32& rvaImportDescriptor,
    const uint_32& sizeOfImportDescriptor,
    const pe_import_vec& imports
): m_name(name), m_rvaImportDescriptor(rvaImportDescriptor), m_sizeOfImportDescriptor(sizeOfImportDescriptor), m_imports(imports)
{ }

std::string CPeModule::name() const
{
    return m_name;
}

uint_32 CPeModule::rvaImportDescriptor() const
{
    return m_rvaImportDescriptor;
}

uint_32 CPeModule::sizeOfImportDescriptor() const
{
    return m_sizeOfImportDescriptor;
}

import_vec CPeModule::imports() const
{
    const auto pe = peImports();
    auto res = import_vec { };
    res.reserve(pe.size());

    for (const auto& import : pe) {
        res.push_back(std::static_pointer_cast<IImport>(import));
    }

    return res;
}

pe_import_vec CPeModule::peImports() const
{
    return m_imports;
}

