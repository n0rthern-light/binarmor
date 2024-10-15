#ifndef CORE_FORMAT_PE__PE_FORMAT_HPP_
#define CORE_FORMAT_PE__PE_FORMAT_HPP_

#include "../IFormat.hpp"
#include "../../shared/Binary.hpp"
#include "PeSection.hpp"
#include "PeModule.hpp"
#include "../../shared/BinaryPointer.hpp"
#include "../../shared/SectionPermissions.hpp"
#include "core/format/IImport.hpp"
#include "core/format/IModule.hpp"
#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"

namespace program::core::format::pe {
    class CPeFormat : public IFormat
    {
        program::core::shared::CBinary m_binary;
    public:
        CPeFormat(const CPeFormat& other);
        CPeFormat(const program::core::shared::CBinary& binary);
        program::core::shared::Format format() const;
        program::core::shared::CBinary binary() const;
        byte_vec bytes() const;
        program::core::shared::Architecture architecture() const;
        program::core::shared::Type type() const;
        program::core::shared::Endianness endianness() const;
        AddressType addressType() const;
        CUnsigned entryPoint() const;
        binary_offset rvaToOffset(const binary_offset& rva) const;
        program::core::shared::CBinaryPointer rvaToPointer(const binary_offset& rva) const;
        pe_section_vec peSections() const;
        uint_16 sectionCount() const;
        section_vec sections() const;
        section_ptr findSectionByName(const std::string& name) const;
        pe_module_map peImportModules() const;
        module_map importModules() const;
        import_ptr import(const std::string& module, const std::string& function) const;
        CPeFormat addPeSection(
            const std::string& name,
            binary_offset size,
            const program::core::shared::CSectionPermissions permissions
        ) const;
        format_ptr addSection(
            const std::string& name,
            binary_offset size,
            const program::core::shared::CSectionPermissions permissions
        ) const;
        format_ptr changeBytes(
            const byte_vec& bytes
        ) const;
    };
}

#endif // CORE_FORMAT_PE__PE_FORMAT_HPP_
