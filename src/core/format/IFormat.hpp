#ifndef CORE_FORMAT__I_FORMAT_HPP_
#define CORE_FORMAT__I_FORMAT_HPP_

#include "../shared/attributes.hpp"
#include <memory>
#include <shared/value/Unsigned.hpp>
#include "ISection.hpp"
#include "core/format/IModule.hpp"
#include "core/shared/Binary.hpp"
#include "shared/types/defines.hpp"

class IFormat;

typedef std::shared_ptr<IFormat> format_ptr;

class IFormat
{
public:
    virtual ~IFormat() { };
    virtual Format format() const = 0;
    virtual byte_vec bytes() const = 0;
    virtual CBinary binary() const = 0;
    virtual Architecture architecture() const = 0;
    virtual Type type() const = 0;
    virtual Endianness endianness() const = 0;
    virtual AddressType addressType() const = 0;
    virtual CUnsigned entryPoint() const = 0;
    virtual uint_16 sectionCount() const = 0;
    virtual section_vec sections() const = 0;
    virtual section_ptr findSectionByName(const std::string& name) const = 0;
    virtual module_map importModules() const = 0;
    virtual import_ptr import(const std::string& module, const std::string& function) const = 0;
    virtual format_ptr addSection(
        const std::string& name,
        binary_offset size,
        const CSectionPermissions permissions
    ) const = 0;
    virtual format_ptr changeBytes(
        const byte_vec& bytes
    ) const = 0;
};

#endif // CORE_FORMAT__I_FORMAT_HPP_
