#ifndef CORE_FORMAT__I_SECTION_HPP_
#define CORE_FORMAT__I_SECTION_HPP_

#include "core/shared/SectionPermissions.hpp"
#include "shared/types/defines.hpp"
#include <string>
#include <shared/value/Unsigned.hpp>

namespace program::core::format {
    class ISection;

    typedef std::shared_ptr<ISection> section_ptr;
    typedef std::vector<section_ptr> section_vec;

    class ISection {
    public:
        virtual ~ISection() = default;

        virtual std::string name() const = 0;
        virtual CUnsigned baseAddress() const = 0;
        virtual size_t size() const = 0;
        virtual binary_offset headerOffset() const = 0;
        virtual program::core::shared::CSectionPermissions permissions() const = 0;
        virtual unsigned char nullByteRepresentation() const = 0;
    };
}

#endif // CORE_FORMAT__I_SECTION_HPP_
